// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseDialogueParticipantComponent.generated.h"

class USpeakerAsset;
class UDialogueAsset;
class UDialogueInstance;

UCLASS(Blueprintable, Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDBOX_API UBaseDialogueParticipantComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool CanStartDialogue(FString TopicName) const;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	TArray<UDialogueAsset*> GetAvailableDialogueTopics() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue")
	void NotifyDialogueStarted(UDialogueInstance* DialogueInstance);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue")
	void NotifyDialogueAdvanced(UDialogueInstance* DialogueInstance, const FText& DialogueText);

	UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue")
	void NotifyDialogueFinished(UDialogueInstance* DialogueInstance);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue")
	void PromptForDialogueResponse(UDialogueInstance* DialogueInstance, const TArray<FText>& ResponseOptions);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Component, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpeakerAsset> SpeakerAsset;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	TArray<TObjectPtr<UDialogueAsset>> DialogueAssets;
	
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	TSet<FGuid> ActiveDialogueIds;
};
