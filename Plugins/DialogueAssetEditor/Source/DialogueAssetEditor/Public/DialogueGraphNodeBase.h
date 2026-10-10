#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueNodeType.h"
#include "DialogueGraphNodeBase.generated.h"

UCLASS()
class UDialogueGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()
	
public:
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection direction, FName name) { /* Must be overridden */ return nullptr; }
	virtual UEdGraphPin* CreateDefaultInputPin() { return nullptr; }
	virtual void CreateDefaultOutputPins() { /* Do nothing by default */ }
	
	virtual void InitNodeInfo(UObject* outer) { /* Do nothing by default */ }
	virtual void SetNodeInfo(class UDialogueNodeInfoBase* nodeInfo) { /* None by default */ }
	virtual UDialogueNodeInfoBase* GetNodeInfo() const { /* None by default */ return nullptr; }
	
	virtual EDialogueNodeType GetDialogueNodeType() const { return EDialogueNodeType::Unknown; }
};
