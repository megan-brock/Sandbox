#pragma once

#include "CoreMinimal.h"
#include "DialogueInstance.generated.h"

class UDialogueRuntimeNode;
class USpeakerAsset;
class UDialogueAsset;
class UBaseDialogueParticipantComponent;

UCLASS(BlueprintType)
class UDialogueInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDialogueAsset> DialogueAsset;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UBaseDialogueParticipantComponent>> Participants;

	UPROPERTY(BLueprintReadOnly)
	FGuid DialogueId;
	
public:
	void StartDialogue();
	
	UFUNCTION(BlueprintCallable)
	void AdvanceDialogue(int ChoiceIndex);
	
private:
	UPROPERTY()
	TObjectPtr<UDialogueRuntimeNode> CurrentNode;
	
private:
	void NotifyParticipantsDialogueStarted() const;
	
	void NotifyParticipantsDialogueAdvanced() const;
	
	void NotifyParticipantsDialogueFinished() const;

	TArray<FText> GetDialoguePrompts(USpeakerAsset* Speaker) const;
};
