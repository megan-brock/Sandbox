#pragma once

#include "CoreMinimal.h"
#include "DialogueAssetFactory.generated.h"

UCLASS()
class UDialogueAssetFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	UDialogueAssetFactory(const FObjectInitializer& ObjectInitializer);
	
public:
	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool CanCreateNew() const override;
	// UFactory interface
	
};
