#pragma once

#include "DialogueNodeInfoBase.h"
#include "DialogueStartNodeInfo.generated.h"

UCLASS(Blueprintable)
class DIALOGUEASSETEDITORRUNTIME_API UDialogueStartNodeInfo : public UDialogueNodeInfoBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FText PromptText;
};
