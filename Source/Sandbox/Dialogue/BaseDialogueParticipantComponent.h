// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueAsset.h"
#include "BaseDialogueParticipantComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConversationStarted, UBaseDialogueParticipantComponent*, OtherParticipant);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogueFinished, EDialogueNodeAction, Action, const FString&, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialoguePrompted);

UCLASS(Blueprintable, Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDBOX_API UBaseDialogueParticipantComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBaseDialogueParticipantComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool HasConversationTopic(FString TopicName) const;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	UDialogueAsset* GetConversationTopic(FString TopicName) const;
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void AddConversationTopic(FString TopicName);
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void RemoveConversationTopic(FString TopicName);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	TArray<FText> GetDialoguePrompts();
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void EnterConversation();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartDialogue(FString TopicName);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void AdvanceDialogue(FString TopicName, int DialogueOptionIndex);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Component, meta=(AllowPrivateAccess = "true"))
	FName ParticipantId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	TArray<UDialogueAsset*> DialogueAssets;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnConversationStarted OnConversationStarted;
	
	UPROPERTY()
	class UDialogueRuntimeNode* CurrentNode;
	
	UPROPERTY( BlueprintAssignable, Category = "Events")
	FOnDialogueFinished OnDialogueFinished;
	
	UPROPERTY( BlueprintAssignable, Category = "Events")
	FOnDialoguePrompted OnDialoguePrompted;
};
