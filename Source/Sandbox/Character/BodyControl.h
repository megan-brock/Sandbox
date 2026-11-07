#pragma once

#include "CoreMinimal.h"
#include "BodyControlData.h"
#include "UObject/Object.h"
#include "BodyControl.generated.h"

class UBodyControl;

DECLARE_DYNAMIC_DELEGATE_OneParam(FBodyControlTargetReachedCallback, UBodyControl*, BodyControl);
DECLARE_DYNAMIC_DELEGATE_OneParam(FBodyControlTargetCancelledCallback, UBodyControl*, BodyControl);

UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class UBodyControl : public UObject
{
public:
	GENERATED_BODY()
	
public:
	void Tick(float DeltaTime);
	
public:
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void MoveTowards(
		FVector NewTargetLocation, FRotator NewTargetRotation,
		FBodyControlTargetReachedCallback OnTargetReached, FBodyControlTargetCancelledCallback OnTargetCancelled);
	
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void MoveToRest(FBodyControlTargetReachedCallback OnTargetReached, FBodyControlTargetCancelledCallback OnTargetCancelled);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = BodyControl)
	bool GetIsUserControlled();
	
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void SetIsUserControlled(bool IsControlled);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = BodyControl)
	bool GetIsControlled();
	
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void SetIsControlled(bool IsControlled);
	
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void SetIsAnimating(bool IsAnimating);
	
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void SetShouldWatch(bool ShouldWatch);
	
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void SetIsReaching(bool IsReaching);
	
	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void SnapTo(FVector NewLocation, FRotator NewRotation);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = BodyControl)
	bool HasReachedTarget() const;

	UFUNCTION(BlueprintCallable, Category = BodyControl)
	void SetRestLocationAndRotation(FVector Location, FRotator Rotation, bool SnapToTarget);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyControl)
	FBodyControlData Data;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BodyControl)
	float LocationReachedTolerance = 0.1f;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> Mesh;
	
private:
	UPROPERTY()
	FBodyControlTargetReachedCallback TargetReachedCallback;
	
	UPROPERTY()
	FBodyControlTargetCancelledCallback TargetCancelledCallback;
	
	bool bHasReachedTarget = false;
	bool bHasTarget = false;
	
	void CheckTargetReached();
	
	void CancelCurrentMovement();
};
