#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"
#include "SGraphPin.h"

class SDialoguePin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialoguePin){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);
protected:
	//~ Begin SGraphPin Interface
	virtual FSlateColor GetPinColor() const override;
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
	//~ End SGraphPin Interface

	const FSlateBrush* GetPinBorder() const;
};

class SGraphNodeDialogue : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SGraphNodeDialogue) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs, UEdGraphNode* InNode);

	virtual void CreatePinWidgets() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	virtual void UpdateGraphNode() override;
	virtual void SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel) override;
	
protected:
	TSharedPtr<SHorizontalBox> OutputPinBox;
};
