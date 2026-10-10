// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseDialogueParticipantComponent.h"
#include "DialogueAsset.h"
#include "DialogueNodeInfo.h"
#include "SpeakerAsset.h"

DEFINE_LOG_CATEGORY_STATIC(DialogueParticipantComponentSub, Log, All);

UBaseDialogueParticipantComponent::UBaseDialogueParticipantComponent()
{
}

bool UBaseDialogueParticipantComponent::HasConversationTopic(const FString TopicName) const
{
	for (auto dialogueAsset : DialogueAssets)
	{
		if (dialogueAsset->DialogueName == TopicName)
		{
			return true;
		}
	}
	return false;
}

UDialogueAsset* UBaseDialogueParticipantComponent::GetConversationTopic(FString TopicName) const
{
	for (auto dialogueAsset : DialogueAssets)
	{
		if (dialogueAsset->DialogueName == TopicName)
		{
			return dialogueAsset;
		}
	}
	return nullptr;
}

void UBaseDialogueParticipantComponent::AddConversationTopic(const FString TopicName)
{
}

void UBaseDialogueParticipantComponent::RemoveConversationTopic(FString TopicName)
{
}

TArray<FText> UBaseDialogueParticipantComponent::GetDialoguePrompts()
{
	if (CurrentNode == nullptr || CurrentNode->OutputPins.Num() == 0)
	{
		return {};
	}
	
	TArray<FText> prompts;	
	for (auto connection : CurrentNode->OutputPins[0]->Connections)
	{
		prompts.Add(Cast<UDialogueNodeInfo>(connection->Parent->NodeInfo)->DialogText);
	}
	
	return prompts;
}

void UBaseDialogueParticipantComponent::EnterConversation()
{

}

void UBaseDialogueParticipantComponent::StartDialogue(FString TopicName)
{
	auto dialogueAsset = GetConversationTopic(TopicName);
	if (dialogueAsset == nullptr)
	{
		UE_LOG(DialogueParticipantComponentSub, Error, TEXT("UDialogueParticipantComponent::StartDialogue: Does not have topic %s"), *TopicName);
		return;
	}
	
	
}

void UBaseDialogueParticipantComponent::AdvanceDialogue(FString TopicName, int index)
{
	if (!HasConversationTopic(TopicName))
	{
		UE_LOG(DialogueParticipantComponentSub, Error, TEXT("UDialogueParticipantComponent::StartDialogue: Does not have topic %s"), *TopicName);
		return;
	}
	
	if (CurrentNode == nullptr)
	{
		UE_LOG(DialogueParticipantComponentSub, Error, TEXT("UDialogueParticipantComponent::AdvanceDialogue: Not currently in dialogue"));
	}
	
	if (CurrentNode->OutputPins.Num() == 0)
	{
		// TODO exit conversation
	}
	
	if (index >= CurrentNode->OutputPins[0]->Connections.Num() || index < 0) {
		UE_LOG(DialogueParticipantComponentSub, Error, TEXT("UDialogueParticipantComponent::AdvanceDialogue: Invalid response option at index %d"), index);
		return;
	}

	CurrentNode = CurrentNode->OutputPins[0]->Connections[index]->Parent;
}
