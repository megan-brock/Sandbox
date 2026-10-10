#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class SpeakerAssetAction : public FAssetTypeActions_Base
{
public:
	SpeakerAssetAction(EAssetTypeCategories::Type Category);
	
public:
	// FAssetTypeActions_Base interface
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;
	// FAssetTypeActions_Base interface
	
private:
	EAssetTypeCategories::Type AssetCategory;
};
