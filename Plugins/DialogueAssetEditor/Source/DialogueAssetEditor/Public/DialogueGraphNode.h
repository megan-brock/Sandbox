#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeBase.h"
#include "DialogueNodeInfo.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogueGraphNode.generated.h"

UCLASS()
class UDialogueGraphNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()
public:
	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Green); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
	// UEdGraphNode interface

	// UDialogueGraphNodeBase interface
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;
	
	virtual UEdGraphPin* CreateDefaultInputPin() override;
	virtual void CreateDefaultOutputPins() override;
	
	virtual void InitNodeInfo(UObject* outer) override { NodeInfo = NewObject<class UDialogueNodeInfo>(outer); }
	virtual void SetNodeInfo(class UDialogueNodeInfoBase* nodeInfo) override { NodeInfo = Cast<class UDialogueNodeInfo>(nodeInfo); }
	virtual UDialogueNodeInfoBase* GetNodeInfo() const override { return NodeInfo; }
	virtual UDialogueNodeInfo* GetDialogueNodeInfo() const { return Cast<UDialogueNodeInfo>(NodeInfo); }
	
	virtual EDialogueNodeType GetDialogueNodeType() const override { return EDialogueNodeType::DialogueNode; }
	// UDialogueGraphNodeBase interface
	
protected:
	UPROPERTY()
	class UDialogueNodeInfo* NodeInfo = nullptr;
};
