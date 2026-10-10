#include "SGraphNodeDialogue.h"

#include "DialogueGraphNode.h"
#include "SGraphPin.h"

void SDialoguePin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	this->SetCursor(EMouseCursor::Default);

	bShowLabel = true;

	GraphPinObj = InPin;
	check(GraphPinObj != NULL);

	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	SBorder::Construct(SBorder::FArguments()
		.BorderImage(this, &SDialoguePin::GetPinBorder)
		.BorderBackgroundColor(this, &SDialoguePin::GetPinColor)
		.OnMouseButtonDown(this, &SDialoguePin::OnPinMouseDown)
		.Cursor(this, &SDialoguePin::GetPinCursor)
		.Padding(FMargin(10.0f))
		);
}

FSlateColor SDialoguePin::GetPinColor() const
{
	return FSlateColor(FLinearColor(0.2f, 1.0f, 0.2f));
}

TSharedRef<SWidget> SDialoguePin::GetDefaultValueWidget()
{
	return SNew(STextBlock);
}

const FSlateBrush* SDialoguePin::GetPinBorder() const
{
	return FAppStyle::GetBrush(TEXT("Graph.StateNode.Body"));
}

void SGraphNodeDialogue::Construct(const FArguments& InArgs, UEdGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

void SGraphNodeDialogue::CreatePinWidgets()
{
	UDialogueGraphNode* dialogueNode = Cast<UDialogueGraphNode>(GraphNode);
	for (int32 PinIdx = 0; PinIdx < dialogueNode->Pins.Num(); PinIdx++)
	{
		UEdGraphPin* MyPin = dialogueNode->Pins[PinIdx];
		if (!MyPin->bHidden)
		{
			TSharedPtr<SGraphPin> NewPin = SNew(SDialoguePin, MyPin);
				// .ToolTipText( this, &SGraphNode_BehaviorTree::GetPinTooltip, MyPin);

			AddPin(NewPin.ToSharedRef());
		}
	}
}

void SGraphNodeDialogue::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));
	if (PinToAdd->GetDirection() == EGPD_Input)
	{
		LeftNodeBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillHeight(1.0f)
			.Padding(20.0f,0.0f)
			[
				PinToAdd
			];
		InputPins.Add(PinToAdd);
	}
	else
	{
		OutputPinBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillWidth(1.0f)
			[
				PinToAdd
			];
		OutputPins.Add(PinToAdd);
	}
}

void SGraphNodeDialogue::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();
	LeftNodeBox.Reset();
	RightNodeBox.Reset();
	
	this->GetOrAddSlot(ENodeZone::Center)
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Center)
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("Graph.StateNode.Body"))
		.BorderBackgroundColor(FLinearColor(0.2f, 0.2f, 0.2f, 1.0f))
		.Padding(0.0f)
		.VAlign(VAlign_Center)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)

				// INPUT PIN AREA
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SBox)
					.MinDesiredHeight(8.0f)
					[
						SAssignNew(LeftNodeBox, SVerticalBox)
					]
				]

				// TITLE AREA
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::GetBrush("Graph.Node.TitleBackground"))
					.BorderBackgroundColor(GraphNode->GetNodeTitleColor())
					[
						SNew(STextBlock)
						.Text(GraphNode->GetNodeTitle(ENodeTitleType::FullTitle))
						.TextStyle(FAppStyle::Get(), "Graph.Node.TitleFont")
					]
				]

				// OUTPUT PIN AREA
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SBox)
					.MinDesiredHeight(8.0f)
					[
						SAssignNew(RightNodeBox, SVerticalBox)
						+SVerticalBox::Slot()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.Padding(20.0f,0.0f)
						.FillHeight(1.0f)
						[
							SAssignNew(OutputPinBox, SHorizontalBox)
						]
					]
				]
			]
		]
	];

	// Important: Tell SGraphNode to auto-generate the pin widgets into LeftNodeList & RightNodeList
	CreatePinWidgets();
}

void SGraphNodeDialogue::SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel)
{
	SGraphNode::SetOwner(OwnerPanel);

	// for (auto& ChildWidget : SubNodes)
	// {
	// 	if (ChildWidget.IsValid())
	// 	{
	// 		ChildWidget->SetOwner(OwnerPanel);
	// 		OwnerPanel->AttachGraphEvents(ChildWidget);
	// 	}
	// }
}
