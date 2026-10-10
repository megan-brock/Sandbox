#include "DialogueStartGraphNode.h"

UEdGraphPin* UDialogueStartGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	return CreatePin(Direction, TEXT("Outputs"), TEXT("StartPin"), Name);
}
