#include "SpeakerAssetFactory.h"
#include "SpeakerAsset.h"

USpeakerAssetFactory::USpeakerAssetFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = USpeakerAsset::StaticClass();
}
	
UObject* USpeakerAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	USpeakerAsset* NewSpeakerAsset = NewObject<USpeakerAsset>(InParent, Class, Name, Flags);
	return NewSpeakerAsset;
}

bool USpeakerAssetFactory::CanCreateNew() const
{
	return true;
}
