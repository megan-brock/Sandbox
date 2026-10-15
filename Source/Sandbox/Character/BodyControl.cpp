#include "BodyControl.h"

UBodyControl::UBodyControl()
{
}

void UBodyControl::Tick(float DeltaTime)
{
	if (Data.IsControlled)
	{
		Data.CurrentLocation = FMath::Lerp(Data.CurrentLocation, Data.TargetLocation, DeltaTime * 10.0f);
		Data.CurrentRotation = FMath::Lerp(Data.CurrentRotation, Data.TargetRotation, DeltaTime * 10.0f);
	}
}

void UBodyControl::MoveTowards(
	FVector NewCurrentLocation, FRotator NewCurrentRotation, 
	FVector NewTargetLocation, FRotator NewTargetRotation,
	FBodyControlTargetReachedCallback OnTargetReached)
{
	Data.CurrentLocation = NewCurrentLocation;
	Data.CurrentRotation = NewCurrentRotation;
	
	Data.TargetLocation = NewTargetLocation;
	Data.TargetRotation = NewTargetRotation;
	
	Data.IsControlled = true;
	
	TargetReachedCallback = OnTargetReached;
	bHasReachedTarget = false;

	CheckTargetReached();
}

void UBodyControl::SetIsControlled(bool IsControlled)
{
	Data.IsControlled = IsControlled;
}

void UBodyControl::SnapTo(FVector NewLocation, FRotator NewRotation)
{
	Data.CurrentLocation = Data.TargetLocation = NewLocation;
	Data.CurrentRotation = Data.TargetRotation = NewRotation;
	Data.IsControlled = true;
}

void UBodyControl::RotateTowards(FRotator NewTargetRotation)
{
	Data.CurrentRotation = Data.TargetRotation = NewTargetRotation;
	Data.IsControlled = true;
}

bool UBodyControl::HasReachedTarget() const
{
	const bool bLocationReached = FVector::DistSquared(Data.CurrentLocation, Data.TargetLocation)
		<= FMath::Square(LocationReachedTolerance);

	const bool bRotationReached = Data.CurrentRotation.Equals(Data.TargetRotation, RotationReachedTolerance);

	return bLocationReached && bRotationReached;
}

void UBodyControl::CheckTargetReached()
{
	if (!Data.IsControlled || bHasReachedTarget)
	{
		return;
	}

	if (!HasReachedTarget())
	{
		return;
	}

	bHasReachedTarget = true;

	if (TargetReachedCallback.IsBound())
	{
		TargetReachedCallback.Execute(this);
	}
}
