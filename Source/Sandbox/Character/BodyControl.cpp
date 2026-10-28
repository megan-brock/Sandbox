#include "BodyControl.h"

void UBodyControl::Tick(float DeltaTime)
{
	if (Data.IsControlled)
	{
		Data.CurrentLocation = FMath::Lerp(Data.CurrentLocation, Data.TargetLocation, DeltaTime * 3.0f);
		Data.CurrentRotation = FMath::Lerp(Data.CurrentRotation, Data.TargetRotation, DeltaTime * 3.0f);
		
		CheckTargetReached();
	}
}

void UBodyControl::MoveTowards(
	FVector NewTargetLocation, FRotator NewTargetRotation,
	FBodyControlTargetReachedCallback OnTargetReached,
	FBodyControlTargetCancelledCallback OnTargetCancelled)
{
	UE_LOG(LogTemp, Warning, TEXT("MoveTowards() From: %s To: %s"), *Data.CurrentLocation.ToString(), *Data.TargetLocation.ToString());
	
	if (TargetReachedCallback.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetReachedCallback() New target, cancelling previous"));
		TargetCancelledCallback.ExecuteIfBound(this);
	}
	
	FTransform CurrentTransform = Mesh->GetBoneTransform(Data.BoneName);
	
	Data.CurrentLocation = CurrentTransform.GetLocation();
	Data.CurrentRotation = CurrentTransform.Rotator();
	
	Data.TargetLocation = NewTargetLocation;
	Data.TargetRotation = NewTargetRotation;
	
	Data.IsControlled = true;
	
	TargetReachedCallback = OnTargetReached;
	TargetCancelledCallback = OnTargetCancelled;
	
	bHasReachedTarget = false;
}

void UBodyControl::MoveToRest(FBodyControlTargetReachedCallback OnTargetReached,
	FBodyControlTargetCancelledCallback OnTargetCancelled)
{
	MoveTowards(Data.RestLocation, Data.RestRotation, OnTargetReached, OnTargetCancelled);
}

bool UBodyControl::GetIsControlled()
{
	return Data.IsControlled;
}

void UBodyControl::SetIsControlled(bool IsControlled)
{
	Data.IsControlled = IsControlled;
}

void UBodyControl::SetShouldWatch(bool ShouldWatch)
{
	Data.ShouldWatch = ShouldWatch;
}

void UBodyControl::SnapTo(FVector NewLocation, FRotator NewRotation)
{
	Data.CurrentLocation = Data.TargetLocation = NewLocation;
	Data.CurrentRotation = Data.TargetRotation = NewRotation;
}

bool UBodyControl::HasReachedTarget() const
{
	const bool bLocationReached = FVector::DistSquared(Data.CurrentLocation, Data.TargetLocation)
		<= FMath::Square(LocationReachedTolerance);

	return bLocationReached;
}

void UBodyControl::SetRestLocationAndRotation(FVector Location, FRotator Rotation, bool SnapToTarget)
{
	Data.RestLocation = Location;
	Data.RestRotation = Rotation;
	
	if (SnapToTarget)
	{
		SnapTo(Location, Rotation);
	}
}

void UBodyControl::CheckTargetReached()
{
	if (bHasReachedTarget)
	{
		return;
	}

	if (!HasReachedTarget())
	{
		return;
	}

	bHasReachedTarget = true;

	UE_LOG(LogTemp, Warning, TEXT("TargetReachedCallback() Target %s reached"), *Data.TargetLocation.ToString());
	
	const FBodyControlTargetReachedCallback CallbackToExecute = TargetReachedCallback;

	TargetReachedCallback.Unbind();
	TargetCancelledCallback.Unbind();

	CallbackToExecute.ExecuteIfBound(this);
}
