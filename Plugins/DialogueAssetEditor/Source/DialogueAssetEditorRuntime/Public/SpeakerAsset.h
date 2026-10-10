#pragma once

#include "CoreMinimal.h"
#include "SpeakerAsset.generated.h"

UCLASS(BlueprintType)
class DIALOGUEASSETEDITORRUNTIME_API USpeakerAsset : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SpeakerName = TEXT("Enter speaker name here");
};
