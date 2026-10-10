#include "DialogueGraphSchema.h"
#include "DialogueGraphNode.h"
#include "DialogueNodeInfo.h"
#include "DialogueStartGraphNode.h"

void UDialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FNewNodeAction> newNodeAction = MakeShareable(
		new FNewNodeAction(
			UDialogueGraphNode::StaticClass(),
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New Dialogue Node")),
			FText::FromString(TEXT("Makes a new dialogue node")),
			0
		)
	);
	
	ContextMenuBuilder.AddAction(newNodeAction);
}

const FPinConnectionResponse UDialogueGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	if (A == nullptr || B == nullptr)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Invalid pin"));
	}
	
	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Inputs can only connect to outputs"));
	}

	if (A->Direction == EGPD_Input)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, TEXT(""));
	}
	else
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_B, TEXT(""));
	}
}

void UDialogueGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	UDialogueStartGraphNode* startNode = NewObject<UDialogueStartGraphNode>(&Graph);
	startNode->CreateNewGuid();
	startNode->NodePosX = 0;
	startNode->NodePosY = 0;
	startNode->InitNodeInfo(startNode);
	
	startNode->CreateDialoguePin(EGPD_Output, FName(TEXT("Start")));
	Graph.AddNode(startNode, true, true);
	Graph.Modify();
}

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UDialogueGraphNodeBase* result = NewObject<UDialogueGraphNodeBase>(ParentGraph, ClassTemplate);
	result->CreateNewGuid();
	result->NodePosX = Location.X;
	result->NodePosY = Location.Y;
	result->InitNodeInfo(result);
	
	UEdGraphPin* inputPin = result->CreateDefaultInputPin();
	result->CreateDefaultOutputPins();
	
	if (FromPin != nullptr)
	{
		result->GetSchema()->TryCreateConnection(FromPin, inputPin);
	}
	
	ParentGraph->Modify();
	ParentGraph->AddNode(result, true, true);
	
	return result;
}
