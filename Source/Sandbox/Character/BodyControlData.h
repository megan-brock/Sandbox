#pragma once

#include "CoreMinimal.h"
#include "BodyControlData.generated.h"

USTRUCT(BlueprintType)
struct FBodyControlData
{
public:
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	FName BoneName;
	
	UPROPERTY()
	FVector TargetLocation = FVector::ZeroVector;
	
	UPROPERTY()
	FRotator TargetRotation = FRotator::ZeroRotator;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	FVector RestLocation = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	FRotator RestRotation = FRotator::ZeroRotator;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	FVector CurrentLocation = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	FRotator CurrentRotation = FRotator::ZeroRotator;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	bool IsControlled = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	bool IsUserControlled = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	bool IsReaching = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	bool IsAnimating = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	bool ShouldWatch = false;
};
