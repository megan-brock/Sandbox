#pragma once

#include "CoreMinimal.h"
#include "BodyControlData.h"
#include "UObject/Object.h"
#include "BodyControl.generated.h"

UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class UBodyControl : public UObject
{
public:
	GENERATED_BODY()
	
public:
	UBodyControl();
	
	void Tick(float DeltaTime);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	FBodyControlData Data;
	
public:
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void MoveTowards(FVector NewCurrentLocation, FRotator NewCurrentRotation, FVector NewTargetLocation, FRotator NewTargetRotation);
	
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void SnapTo(FVector NewLocation, FRotator NewRotation);
	
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void RotateTowards(FRotator NewTargetRotation);
};
