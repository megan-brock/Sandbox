// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterControlComponent.h"

// Sets default values for this component's properties
UCharacterControlComponent::UCharacterControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	HeadBoneRotation = FRotator::ZeroRotator;
	RightHandTarget = FTransform::Identity;
	
	IsControllingHand = false;
	IsSitting = false;
}

bool UCharacterControlComponent::GetIsSitting() const
{
	return IsSitting;
}

void UCharacterControlComponent::SetIsSitting(const bool NewIsSitting)
{
	IsSitting = NewIsSitting;
}
