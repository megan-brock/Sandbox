#include "DialogueSubsystem.h"
#include "DialogueAsset.h"
#include "DialogueInstance.h"

UDialogueInstance* UDialogueSubsystem::StartDialogue(UDialogueAsset* DialogueAsset,	const TArray<UBaseDialogueParticipantComponent*>& Participants)
{
	if (!DialogueAsset)
	{
		return nullptr;
	}

	UDialogueInstance* Instance = NewObject<UDialogueInstance>(this);

	Instance->DialogueId = FGuid::NewGuid();
	Instance->DialogueAsset = DialogueAsset;
	Instance->Participants = Participants;

	Instance->StartDialogue();

	ActiveDialogueInstances.Add(Instance->DialogueId, Instance);

	return Instance;
}

void UDialogueSubsystem::EndDialogue(FGuid ConversationId)
{
	ActiveDialogueInstances.Remove(ConversationId);
}

UDialogueInstance* UDialogueSubsystem::GetDialogueInstance(FGuid ConversationId) const
{
	return ActiveDialogueInstances.FindRef(ConversationId);
}
