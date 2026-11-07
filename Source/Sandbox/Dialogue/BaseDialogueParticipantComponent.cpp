// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseDialogueParticipantComponent.h"
#include "DialogueAsset.h"

bool UBaseDialogueParticipantComponent::CanStartDialogue(const FString TopicName) const
{
	if (ActiveDialogueIds.Num() > 0)
	{
		return false;
	}
	
	for (auto dialogueAsset : DialogueAssets)
	{
		if (dialogueAsset->DialogueName == TopicName)
		{
			return true;
		}
	}
	return false;
}

TArray<UDialogueAsset*> UBaseDialogueParticipantComponent::GetAvailableDialogueTopics() const
{
	return DialogueAssets;
}
