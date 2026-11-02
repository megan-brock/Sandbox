#include "BodyControl.h"

void UBodyControl::Tick(float DeltaTime)
{
	if (bHasTarget)
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
	CancelCurrentMovement();
	
	FTransform CurrentTransform = Mesh->GetBoneTransform(Data.BoneName);
	
	Data.CurrentLocation = CurrentTransform.GetLocation();
	Data.CurrentRotation = CurrentTransform.Rotator();
	
	Data.TargetLocation = NewTargetLocation;
	Data.TargetRotation = NewTargetRotation;
	
	Data.IsControlled = true;
	
	Data.IsReaching = true;
	
	TargetReachedCallback = OnTargetReached;
	TargetCancelledCallback = OnTargetCancelled;
	
	bHasTarget = true;
	bHasReachedTarget = false;
}

void UBodyControl::MoveToRest(FBodyControlTargetReachedCallback OnTargetReached,
	FBodyControlTargetCancelledCallback OnTargetCancelled)
{
	MoveTowards(Data.RestLocation, Data.RestRotation, OnTargetReached, OnTargetCancelled);
}

bool UBodyControl::GetIsUserControlled()
{
	return Data.IsUserControlled;
}

void UBodyControl::SetIsUserControlled(bool IsControlled)
{
	Data.IsUserControlled = IsControlled;
}

bool UBodyControl::GetIsControlled()
{
	return Data.IsControlled;
}

void UBodyControl::SetIsControlled(bool IsControlled)
{
	Data.IsControlled = IsControlled;
}

void UBodyControl::SetIsAnimating(bool IsAnimating)
{
	Data.IsAnimating = IsAnimating;
}

void UBodyControl::SetShouldWatch(bool ShouldWatch)
{
	Data.ShouldWatch = ShouldWatch;
}

void UBodyControl::SetIsReaching(bool IsReaching)
{
	Data.IsReaching = IsReaching;
}

void UBodyControl::SnapTo(FVector NewLocation, FRotator NewRotation)
{
	CancelCurrentMovement();
	
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

	Data.IsReaching = false;
	bHasReachedTarget = true;
	bHasTarget = false;
	
	const FBodyControlTargetReachedCallback CallbackToExecute = TargetReachedCallback;

	TargetReachedCallback.Unbind();
	TargetCancelledCallback.Unbind();

	CallbackToExecute.ExecuteIfBound(this);
}

void UBodyControl::CancelCurrentMovement()
{
	if (!bHasTarget)
	{
		return;
	}
	
	const FBodyControlTargetCancelledCallback CallbackToExecute = TargetCancelledCallback;
	
	TargetReachedCallback.Unbind();
	TargetCancelledCallback.Unbind();
	
	if (CallbackToExecute.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("CancelCurrentMovement() Cancelling bound movement"));

		CallbackToExecute.ExecuteIfBound(this);
	}

	bHasTarget = false;
	bHasReachedTarget = false;
	Data.IsReaching = false;
}
