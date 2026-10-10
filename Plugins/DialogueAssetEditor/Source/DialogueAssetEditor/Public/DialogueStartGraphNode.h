#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogueGraphNode.h"
#include "DialogueStartNodeInfo.h"
#include "DialogueStartGraphNode.generated.h"

UCLASS()
class UDialogueStartGraphNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()
	
public:
	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Start"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(1.0f, 0.2f, 0.6f); }
	virtual bool CanUserDeleteNode() const override { return false; }
	// UEdGraphNode interface
	
	// UDialogueGraphNodeBase interface
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection direction, FName name) override;
	virtual EDialogueNodeType GetDialogueNodeType() const override { return EDialogueNodeType::StartNode; }
	
	virtual void InitNodeInfo(UObject* outer) override { NodeInfo = NewObject<class UDialogueStartNodeInfo>(outer); }
	virtual UDialogueNodeInfoBase* GetNodeInfo() const override { return NodeInfo; }
	virtual void SetNodeInfo(class UDialogueNodeInfoBase* nodeInfo) override { NodeInfo = nodeInfo; }
	// UDialogueGraphNodeBase interface

	virtual UDialogueStartNodeInfo* GetDialogueStartNodeInfo() const { return Cast<UDialogueStartNodeInfo>(NodeInfo); }
	
protected:
	UDialogueNodeInfoBase* NodeInfo = nullptr;
};
