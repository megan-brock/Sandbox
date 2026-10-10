#include "DialogueGraphNode.h"
#include "DialogueNodeInfo.h"
#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"

FText UDialogueGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (NodeInfo == nullptr)
	{
		return FText::GetEmpty();
	}
	
	UDialogueNodeInfo* nodeInfo = GetDialogueNodeInfo();
	FString dialogueTextStr = nodeInfo->DialogText.ToString();
	if (dialogueTextStr.Len() > 15)
	{
		dialogueTextStr = dialogueTextStr.Left(15) + "...";
	}
	return FText::FromString(dialogueTextStr);
}

void UDialogueGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));
	
	UDialogueGraphNode* node = (UDialogueGraphNode*)this;
	section.AddMenuEntry(
		TEXT("DeleteNodeEntry"),
		 FText::FromString(TEXT("Delete Node")),
		 FText::FromString(TEXT("Delete the node")),
		 FSlateIcon(TEXT("DialogueAssetEditorStyle"), TEXT("DialogueAssetNodeDeleteNodeIcon")),
		 FUIAction(FExecuteAction::CreateLambda(
			 [node] ()
			 {
			 	 node->GetGraph()->RemoveNode(node);
			 }
		 ))
	);
}

UEdGraphPin* UDialogueGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName category = (Direction == EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
	FName subCategory = TEXT("DialoguePin");
	
	return CreatePin(Direction, category, subCategory, Name);
}

UEdGraphPin* UDialogueGraphNode::CreateDefaultInputPin()
{
	return CreateDialoguePin(EGPD_Input, TEXT("Display"));
}

void UDialogueGraphNode::CreateDefaultOutputPins()
{
	CreateDialoguePin(EGPD_Output, FName(TEXT("Output")));
}
