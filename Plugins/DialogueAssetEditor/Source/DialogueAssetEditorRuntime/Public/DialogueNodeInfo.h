#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include "SpeakerAsset.h"
#include "DialogueNodeInfo.generated.h"

UENUM(BlueprintType)
enum class EDialogueNodeAction : uint8
{
	Continue,
	ExitTopic,
	ExitConversation,
};

UCLASS(BlueprintType)
class DIALOGUEASSETEDITORRUNTIME_API UDialogueNodeInfo : public UDialogueNodeInfoBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	USpeakerAsset* Speaker;
	
	UPROPERTY(EditAnywhere)
	FText DialogText;
	
	UPROPERTY(EditAnywhere)
	EDialogueNodeAction Action = EDialogueNodeAction::Continue;
};
