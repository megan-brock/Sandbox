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

void UBodyControl::MoveTowards(FVector NewCurrentLocation, FRotator NewCurrentRotation, FVector NewTargetLocation, FRotator NewTargetRotation)
{
	Data.CurrentLocation = NewCurrentLocation;
	Data.CurrentRotation = NewCurrentRotation;
	
	Data.TargetLocation = NewTargetLocation;
	Data.TargetRotation = NewTargetRotation;
	
	Data.IsControlled = true;
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
	
	UE_LOG(LogTemp, Warning, TEXT("RotateTowards %s"), *Data.CurrentRotation.ToString());
}
