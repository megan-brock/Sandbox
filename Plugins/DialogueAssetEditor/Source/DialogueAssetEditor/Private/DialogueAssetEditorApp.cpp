#include "DialogueAssetEditorApp.h"
#include "DialogueAssetAppMode.h"
#include "DialogueAsset.h"
#include "DialogueGraphNode.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "DialogueGraphSchema.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueStartGraphNode.h"

DEFINE_LOG_CATEGORY_STATIC(DialogueAssetEditorAppSub, Log, All);

void DialogueAssetEditorApp::RegisterTabSpawners(const TSharedRef<class FTabManager>& tabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(tabManager);
}

void DialogueAssetEditorApp::InitEditor(const EToolkitMode::Type mode, const TSharedPtr<IToolkitHost>& initToolkitHost, UObject* inObject)
{
	TArray<UObject*> objectsToEdit;
	objectsToEdit.Add(inObject);
	
	WorkingAsset = Cast<UDialogueAsset>(inObject);
	WorkingAsset->SetPreSaveListener([this] () { OnWorkingAssetPreSave(); });
	
	WorkingGraph = FBlueprintEditorUtils::CreateNewGraph(
		WorkingAsset,
		NAME_None,
		UEdGraph::StaticClass(),
		UDialogueGraphSchema::StaticClass());
	
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("DialogueAssetEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(FName(TEXT("DialogueAssetPrimaryTab")), ETabState::OpenedTab)
			)
		);
	
	InitAssetEditor(
		mode,
		initToolkitHost,
		TEXT("DialogueAssetEditor"),
		StandaloneDefaultLayout,
		true, // createStandaloneMenu
		true, // createStandaloneToolbar
		objectsToEdit
	);
	
	AddApplicationMode(TEXT("DialogueAssetAppMode"), MakeShareable(new DialogueAssetAppMode(SharedThis(this))));
	
	SetCurrentMode(TEXT("DialogueAssetAppMode"));
	
	UpdateEditorGraphFromWorkingAsset();
}

void DialogueAssetEditorApp::SetSelectedNodeDetailsView(TSharedPtr<class IDetailsView> detailsView)
{
	SelectedNodeDetailsView = detailsView;
	SelectedNodeDetailsView->OnFinishedChangingProperties().AddRaw(this, &DialogueAssetEditorApp::OnNodeDetailViewPropertiesUpdated);
}

void DialogueAssetEditorApp::OnClose()
{
	UpdateWorkingAssetFromGraph();
	WorkingAsset->SetPreSaveListener(nullptr);
	FAssetEditorToolkit::OnClose();
}

void DialogueAssetEditorApp::OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& event)
{
	if (WorkingGraphUi != nullptr)
	{
		UDialogueGraphNodeBase* node = GetSelectedNode(WorkingGraphUi->GetSelectedNodes());
		if (node != nullptr)
		{
			// node->OnPropertiesChanged();
		}
		
		WorkingGraphUi->NotifyGraphChanged();
	}
}

void DialogueAssetEditorApp::OnWorkingAssetPreSave()
{
	UpdateWorkingAssetFromGraph();
}

void DialogueAssetEditorApp::UpdateWorkingAssetFromGraph()
{
	if (WorkingAsset == nullptr || WorkingGraph == nullptr)
	{
		return;
	}
	
	UDialogueRuntimeGraph* runtimeGraph = NewObject<UDialogueRuntimeGraph>(WorkingAsset);
	WorkingAsset->Graph = runtimeGraph;
	
	TArray<std::pair<FGuid, FGuid>> connections;
	TMap<FGuid, UDialogueRuntimePin*> idToPinMap;
	
	for (UEdGraphNode* uiNode : WorkingGraph->Nodes)
	{
		UDialogueRuntimeNode* runtimeNode = NewObject<UDialogueRuntimeNode>(runtimeGraph);
		runtimeNode->Position = FVector2D(uiNode->NodePosX, uiNode->NodePosY);
		
		for (UEdGraphPin* uiPin : uiNode->Pins)
		{
			UDialogueRuntimePin* runtimePin = NewObject<UDialogueRuntimePin>(runtimeNode);
			runtimePin->PinName = uiPin->PinName;
			runtimePin->PinId = uiPin->PinId;
			runtimePin->Parent = runtimeNode;
			
			if (uiPin->HasAnyConnections() && uiPin->Direction == EGPD_Output)
			{
				for (UEdGraphPin* connectedPin : uiPin->LinkedTo)
				{
					connections.Add(std::make_pair(uiPin->PinId, connectedPin->PinId));
				}
			}
			
			idToPinMap.Add(uiPin->PinId, runtimePin);
			if (uiPin->Direction == EGPD_Input)
			{
				runtimeNode->InputPin = runtimePin;
			}
			else
			{
				runtimeNode->OutputPins.Add(runtimePin);	
			}
		}
		
		UDialogueGraphNodeBase* uiDialogueNode = Cast<UDialogueGraphNodeBase>(uiNode);
		runtimeNode->NodeType = uiDialogueNode->GetDialogueNodeType();
		runtimeNode->NodeInfo = DuplicateObject(uiDialogueNode->GetNodeInfo(), runtimeNode);
		
		runtimeGraph->Nodes.Add(runtimeNode);
	}
	
	for (std::pair<FGuid, FGuid> connection : connections)
	{
		UDialogueRuntimePin* pin1 = idToPinMap[connection.first];
		UDialogueRuntimePin* pin2 = idToPinMap[connection.second];
		pin1->Connections.Add(pin2);
	}
}

void DialogueAssetEditorApp::UpdateEditorGraphFromWorkingAsset()
{
	if (WorkingAsset->Graph == nullptr)
	{
		WorkingGraph->GetSchema()->CreateDefaultNodesForGraph(*WorkingGraph);
		return;
	}
	
	TArray<std::pair<FGuid, FGuid>> connections;
	TMap<FGuid, UEdGraphPin*> idToPinMap;
	
	for (UDialogueRuntimeNode* runtimeNode : WorkingAsset->Graph->Nodes)
	{
		UDialogueGraphNodeBase* newNode = nullptr;
		if (runtimeNode->NodeType == EDialogueNodeType::DialogueNode)
		{
			newNode = NewObject<UDialogueGraphNode>(WorkingGraph);
		}
		else if (runtimeNode->NodeType == EDialogueNodeType::StartNode)
		{
			newNode = NewObject<UDialogueStartGraphNode>(WorkingGraph);
		}
		else
		{
			UE_LOG(DialogueAssetEditorAppSub, Error, TEXT("DialogueAssetEditorApp::UpdateEditorGraphFromWorkingAsset: Unknown dialogue node type %d"), (int32)runtimeNode->NodeType);
			continue;
		}
		
		newNode->CreateNewGuid();
		newNode->NodePosX = runtimeNode->Position.X;
		newNode->NodePosY = runtimeNode->Position.Y;
		
		if (runtimeNode->NodeInfo != nullptr)
		{
			newNode->SetNodeInfo(DuplicateObject(runtimeNode->NodeInfo, newNode));
		}
		else
		{
			newNode->InitNodeInfo(newNode);
		}
		
		if (runtimeNode->InputPin != nullptr)
		{
			UDialogueRuntimePin* pin = runtimeNode->InputPin;
			UEdGraphPin* uiPin = newNode->CreateDialoguePin(EGPD_Input, pin->PinName);
			uiPin->PinId = pin->PinId;
			
			for (UDialogueRuntimePin* connection : pin->Connections)
			{
				connections.Add(std::make_pair(pin->PinId, connection->PinId));
			}
			
			idToPinMap.Add(pin->PinId, uiPin);
		}
		
		for (UDialogueRuntimePin* pin : runtimeNode->OutputPins)
		{
			UEdGraphPin* uiPin = newNode->CreateDialoguePin(EGPD_Output, pin->PinName);
			uiPin->PinId = pin->PinId;
			
			for (UDialogueRuntimePin* connection : pin->Connections)
			{
				connections.Add(std::make_pair(pin->PinId, connection->PinId));
			}
			
			idToPinMap.Add(pin->PinId, uiPin);
		}
		
		WorkingGraph->AddNode(newNode, true, true);
	}
	
	for (std::pair<FGuid, FGuid> connection : connections)
	{
		UEdGraphPin* fromPin = idToPinMap[connection.first];
		UEdGraphPin* toPin = idToPinMap[connection.second];
		fromPin->LinkedTo.Add(toPin);
		toPin->LinkedTo.Add(fromPin);
	}
}

UDialogueGraphNodeBase* DialogueAssetEditorApp::GetSelectedNode(const FGraphPanelSelectionSet& selection) const
{
	for (UObject* obj : selection)
	{
		UDialogueGraphNodeBase* node = Cast<UDialogueGraphNodeBase>(obj);
		if (node != nullptr)
		{
			return node;
		}
	}
	
	return nullptr;
}
void DialogueAssetEditorApp::OnGraphSelectionChanged(const FGraphPanelSelectionSet& selection)
{
	UDialogueGraphNodeBase* selectedNode = GetSelectedNode(selection);
	if (selectedNode != nullptr)
	{
		SelectedNodeDetailsView->SetObject(selectedNode->GetNodeInfo());
	}
	else
	{
		SelectedNodeDetailsView->SetObject(nullptr);
	}
}