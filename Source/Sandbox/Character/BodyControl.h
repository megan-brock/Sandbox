#pragma once

#include "CoreMinimal.h"
#include "BodyControlData.h"
#include "UObject/Object.h"
#include "BodyControl.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FBodyControlTargetReachedCallback, UBodyControl*, BodyControl);

UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class UBodyControl : public UObject
{
public:
	GENERATED_BODY()
	
public:
	UBodyControl();
	
	void Tick(float DeltaTime);
	
public:
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void MoveTowards(
		FVector NewCurrentLocation, FRotator NewCurrentRotation, 
		FVector NewTargetLocation, FRotator NewTargetRotation,
		FBodyControlTargetReachedCallback OnTargetReached);
	
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void SetIsControlled(bool IsControlled);
	
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void SnapTo(FVector NewLocation, FRotator NewRotation);
	
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void RotateTowards(FRotator NewTargetRotation);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = BodyControl)
	bool HasReachedTarget() const;

	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void CheckTargetReached();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	FBodyControlData Data;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BodyControl)
	float LocationReachedTolerance = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BodyControl)
	float RotationReachedTolerance = 1.0f;
	
private:
	UPROPERTY()
	FBodyControlTargetReachedCallback TargetReachedCallback;
	
	bool bHasReachedTarget = false;
};
