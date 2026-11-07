#pragma once

#include "CoreMinimal.h"
#include "DialogueSubsystem.generated.h"

class UDialogueAsset;
class UDialogueInstance;
class UBaseDialogueParticipantComponent;

UCLASS()
class UDialogueSubsystem : public UWorldSubsystem
{
public:
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	UDialogueInstance* StartDialogue(UDialogueAsset* DialogueAsset, const TArray<UBaseDialogueParticipantComponent*>& Participants);

	UFUNCTION(BlueprintCallable)
	void EndDialogue(FGuid ConversationId);

	UFUNCTION(BlueprintCallable)
	UDialogueInstance* GetDialogueInstance(FGuid ConversationId) const;

private:
	UPROPERTY()
	TMap<FGuid, TObjectPtr<UDialogueInstance>> ActiveDialogueInstances;
};