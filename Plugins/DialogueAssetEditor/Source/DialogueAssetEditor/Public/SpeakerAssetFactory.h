#pragma once

#include "CoreMinimal.h"
#include "SpeakerAssetFactory.generated.h"

UCLASS()
class USpeakerAssetFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	USpeakerAssetFactory(const FObjectInitializer& ObjectInitializer);
	
public:
	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool CanCreateNew() const override;
	// UFactory interface
	
};
