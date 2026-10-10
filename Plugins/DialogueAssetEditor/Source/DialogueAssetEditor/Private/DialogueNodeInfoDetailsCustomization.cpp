#include "DialogueNodeInfoDetailsCustomization.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DialogueAsset.h"
#include "DialogueGraphNode.h"
#include "DialogueGraphNodeBase.h"
#include "DialogueNodeInfo.h"
#include "SpeakerAsset.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Text/STextBlock.h"

TSharedRef<IDetailCustomization> FDialogueNodeInfoDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FDialogueNodeInfoDetailsCustomization());
}

void FDialogueNodeInfoDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> EditedObjects;
	DetailBuilder.GetObjectsBeingCustomized(EditedObjects);

	// UObject* EditedObject = EditedObjects.Num() > 0 ? EditedObjects[0].Get() : nullptr;
	// RefreshSpeakerOptions(EditedObject);
	
	for (auto obj : EditedObjects)
	{
		RefreshSpeakerOptions(obj.Get());
	}

	SpeakerPropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogueNodeInfo, Speaker));
	DetailBuilder.HideProperty(SpeakerPropertyHandle);

	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(TEXT("Dialogue"));

	Category.AddCustomRow(FText::FromString(TEXT("Speaker")))
		.NameContent()
		[
			SpeakerPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MinDesiredWidth(250.0f)
		[
			SNew(SComboBox<TSharedPtr<TWeakObjectPtr<USpeakerAsset>>>)
			.OptionsSource(&SpeakerOptions)
			.OnGenerateWidget(this, &FDialogueNodeInfoDetailsCustomization::MakeSpeakerComboWidget)
			.OnSelectionChanged(this, &FDialogueNodeInfoDetailsCustomization::OnSpeakerSelected)
			[
				SNew(STextBlock)
				.Text(this, &FDialogueNodeInfoDetailsCustomization::GetSelectedSpeakerText)
			]
		];
}

void FDialogueNodeInfoDetailsCustomization::RefreshSpeakerOptions(UObject* EditedObject)
{
	if (EditedObject == nullptr)
	{
		return;
	}
	
	SpeakerOptions.Empty();

	if (UDialogueGraphNode* GraphNode = EditedObject->GetTypedOuter<UDialogueGraphNode>())
	{
		if (UEdGraph* Graph = GraphNode->GetGraph())
		{
			UDialogueAsset* DialogueAsset = Cast<UDialogueAsset>(Graph->GetOuter());
			
			if (DialogueAsset == nullptr)
			{
				return;
			}

			for (USpeakerAsset* Speaker : DialogueAsset->Speakers)
			{
				SpeakerOptions.Add(MakeShared<TWeakObjectPtr<USpeakerAsset>>(Speaker));
			}	
		}
	}
}

FText FDialogueNodeInfoDetailsCustomization::GetSelectedSpeakerText() const
{
	UObject* SpeakerObj = nullptr;

	if (SpeakerPropertyHandle.IsValid() && SpeakerPropertyHandle->GetValue(SpeakerObj) == FPropertyAccess::Success)
	{
		if (const USpeakerAsset* Speaker = Cast<USpeakerAsset>(SpeakerObj))
		{
			return FText::FromName(Speaker->SpeakerName);
		}
	}

	return FText::FromString(TEXT("Select Speaker"));
}

TSharedRef<SWidget> FDialogueNodeInfoDetailsCustomization::MakeSpeakerComboWidget(TSharedPtr<TWeakObjectPtr<USpeakerAsset>> SpeakerItem) const
{
	FText SpeakerText = FText::FromString(TEXT("None"));

	if (SpeakerItem.IsValid())
	{
		if (const USpeakerAsset* Speaker = SpeakerItem->Get())
		{
			SpeakerText = FText::FromName(Speaker->SpeakerName);
		}
	}

	return SNew(STextBlock)
		.Text(SpeakerText);
}

void FDialogueNodeInfoDetailsCustomization::OnSpeakerSelected(TSharedPtr<TWeakObjectPtr<USpeakerAsset>> SpeakerItem, ESelectInfo::Type SelectInfo)
{
	if (!SpeakerPropertyHandle.IsValid())
	{
		return;
	}

	USpeakerAsset* SelectedSpeaker = nullptr;

	if (SpeakerItem.IsValid())
	{
		SelectedSpeaker = SpeakerItem->Get();
	}

	SpeakerPropertyHandle->SetValue(SelectedSpeaker);
}