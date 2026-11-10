#include "DialogueInstance.h"

#include "SpeakerAsset.h"
#include "DialogueAsset.h"
#include "DialogueNodeInfo.h"
#include "DialogueRuntimeGraph.h"
#include "BaseDialogueParticipantComponent.h"

DEFINE_LOG_CATEGORY_STATIC(DialogueInstanceSub, Log, All);

TArray<FText> UDialogueInstance::GetDialoguePrompts(USpeakerAsset* Speaker) const
{
	if (CurrentNode == nullptr || CurrentNode->OutputPins.Num() == 0 || CurrentNode->OutputPins[0] == nullptr)
	{
		return {};
	}
	
	TArray<FText> Prompts;

	for (const UDialogueRuntimePin* Connection : CurrentNode->OutputPins[0]->Connections)
	{
		if (Connection == nullptr || Connection->Parent == nullptr)
		{
			UE_LOG(DialogueInstanceSub, Warning, TEXT("UDialogueInstance::GetDialoguePrompts: Skipping invalid dialogue connection"));
			continue;
		}

		const UDialogueNodeInfo* DialogueNodeInfo = Cast<UDialogueNodeInfo>(Connection->Parent->NodeInfo);
		if (DialogueNodeInfo == nullptr)
		{
			UE_LOG(DialogueInstanceSub, Warning, TEXT("UDialogueInstance::GetDialoguePrompts: Connected node does not have UDialogueNodeInfo"));
			continue;
		}

		if (DialogueNodeInfo->Speaker == Speaker)
		{
			Prompts.Add(DialogueNodeInfo->DialogText);
		}
	}
	
	return Prompts;
}

void UDialogueInstance::StartDialogue()
{
	if (DialogueAsset == nullptr)
	{
		UE_LOG(DialogueInstanceSub, Error, TEXT("UDialogueInstance::StartDialogue: Does not have dialogue data"));
		return;
	}
	
	if (DialogueAsset->Graph->Nodes.Num() == 0)
	{
		UE_LOG(DialogueInstanceSub, Error, TEXT("UDialogueInstance::StartDialogue: No dialogue nodes in data %s"), *DialogueAsset->DialogueName);
		return;
	}
	
	CurrentNode = DialogueAsset->Graph->Nodes[0];
	
	NotifyParticipantsDialogueStarted();
	NotifyParticipantsDialogueAdvanced();
}

void UDialogueInstance::AdvanceDialogue(int index)
{
	if (CurrentNode == nullptr)
	{
		UE_LOG(DialogueInstanceSub, Error, TEXT("UDialogueInstance::AdvanceDialogue: Not currently in dialogue"));
		return;
	}
	
	if (CurrentNode->OutputPins.Num() == 0 || CurrentNode->OutputPins[0] == nullptr)
	{
		CurrentNode = nullptr;
		NotifyParticipantsDialogueFinished();
		return;
	}

	const TArray<UDialogueRuntimePin*>& Connections = CurrentNode->OutputPins[0]->Connections;
	
	if (index >= Connections.Num() || index < 0)
	{
		UE_LOG(DialogueInstanceSub, Error, TEXT("UDialogueInstance::AdvanceDialogue: Invalid response option at index %d"), index);
		return;
	}

	if (Connections[index] == nullptr || Connections[index]->Parent == nullptr)
	{
		UE_LOG(DialogueInstanceSub, Error, TEXT("UDialogueInstance::AdvanceDialogue: Response option at index %d has an invalid connection"), index);
		return;
	}

	CurrentNode = Connections[index]->Parent;
	NotifyParticipantsDialogueAdvanced();
}

void UDialogueInstance::NotifyParticipantsDialogueStarted() const
{
	for (UBaseDialogueParticipantComponent* Participant : Participants)
	{
		if (Participant == nullptr)
		{
			continue;
		}
		
		Participant->NotifyDialogueStarted(const_cast<UDialogueInstance*>(this));
	}
}

void UDialogueInstance::NotifyParticipantsDialogueAdvanced() const
{
	if (CurrentNode == nullptr)
	{
		return;
	}
	
	UDialogueNodeInfo* DialogueNodeInfo = Cast<UDialogueNodeInfo>(CurrentNode->NodeInfo);
	if (DialogueNodeInfo == nullptr)
	{
		return;
	}
	
	FText DialogueText = DialogueNodeInfo->DialogText;

	int TotalPrompts = 0;
	for (UBaseDialogueParticipantComponent* Participant : Participants)
	{
		if (Participant == nullptr)
		{
			continue;
		}

		Participant->NotifyDialogueAdvanced(const_cast<UDialogueInstance*>(this), DialogueText);

		const TArray<FText> Prompts = GetDialoguePrompts(Participant->SpeakerAsset);
		if (Prompts.Num() > 0)
		{
			TotalPrompts += Prompts.Num();
			Participant->PromptForDialogueResponse(const_cast<UDialogueInstance*>(this), Prompts);
		}
	}
	
	if (TotalPrompts == 0)
	{
		NotifyParticipantsDialogueFinished();
	}
}

void UDialogueInstance::NotifyParticipantsDialogueFinished() const
{
	for (UBaseDialogueParticipantComponent* Participant : Participants)
	{
		if (Participant == nullptr)
		{
			continue;
		}
		
		Participant->NotifyDialogueFinished(const_cast<UDialogueInstance*>(this));
	}
}
