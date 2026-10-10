#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IDetailLayoutBuilder;
class IPropertyHandle;
class USpeakerAsset;

class FDialogueNodeInfoDetailsCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	void RefreshSpeakerOptions(UObject* EditedObject);
	FText GetSelectedSpeakerText() const;
	TSharedRef<SWidget> MakeSpeakerComboWidget(TSharedPtr<TWeakObjectPtr<USpeakerAsset>> SpeakerItem) const;
	void OnSpeakerSelected(TSharedPtr<TWeakObjectPtr<USpeakerAsset>> SpeakerItem, ESelectInfo::Type SelectInfo);

private:
	TSharedPtr<IPropertyHandle> SpeakerPropertyHandle;
	TArray<TSharedPtr<TWeakObjectPtr<USpeakerAsset>>> SpeakerOptions;
};