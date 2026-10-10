#pragma once

#include "CoreMinimal.h"
#include "DialogueRuntimeGraph.h"
#include "UObject/Object.h"
#include <functional>
#include "DialogueAsset.generated.h"

class USpeakerAsset;

UCLASS(BlueprintType)
class DIALOGUEASSETEDITORRUNTIME_API UDialogueAsset : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DialogueName = TEXT("Enter dialogue name here");
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<USpeakerAsset*> Speakers;
	
	UPROPERTY()
	UDialogueRuntimeGraph* Graph = nullptr;
	
public:
	// UObject interface
	virtual void PreSave(FObjectPreSaveContext saveContext) override;
	// UObject interface

	void SetPreSaveListener(std::function<void()> onPreSaveListener) { OnPreSaveListener = onPreSaveListener; }

private:
	std::function<void()> OnPreSaveListener = nullptr;
};
