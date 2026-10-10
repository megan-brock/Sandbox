#include "SpeakerAssetAction.h"
#include "SpeakerAsset.h"

SpeakerAssetAction::SpeakerAssetAction(EAssetTypeCategories::Type Category)
{
	AssetCategory = Category;
}

FText SpeakerAssetAction::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_SpeakerAsset", "Speaker Asset");
}

FColor SpeakerAssetAction::GetTypeColor() const
{
	return FColor::Green;
}

UClass* SpeakerAssetAction::GetSupportedClass() const
{
	return USpeakerAsset::StaticClass();
}

uint32 SpeakerAssetAction::GetCategories()
{
	return AssetCategory;
}
