#pragma once

#include "CoreMinimal.h"
#include "BodyControlData.generated.h"

USTRUCT(BlueprintType)
struct FBodyControlData
{
public:
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FVector TargetLocation = FVector::ZeroVector;
	
	UPROPERTY()
	FRotator TargetRotation = FRotator::ZeroRotator;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	FVector CurrentLocation = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	FRotator CurrentRotation = FRotator::ZeroRotator;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	bool IsControlled = false;
};
