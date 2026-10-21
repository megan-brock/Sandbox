#include "CharacterControlComponent.h"

#include "SandboxBaseCharacter.h"

UCharacterControlComponent::UCharacterControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	HeadControl = CreateDefaultSubobject<UBodyControl>(TEXT("HeadControl"));
	LeftHandControl = CreateDefaultSubobject<UBodyControl>(TEXT("LeftHandControl"));
	RightHandControl = CreateDefaultSubobject<UBodyControl>(TEXT("RightHandControl"));
	PelvisControl = CreateDefaultSubobject<UBodyControl>(TEXT("PelvisControl"));
	LeftFootControl = CreateDefaultSubobject<UBodyControl>(TEXT("LeftFootControl"));
	RightFootControl = CreateDefaultSubobject<UBodyControl>(TEXT("RightFootControl"));
}

void UCharacterControlComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (ASandboxBaseCharacter* Character = Cast<ASandboxBaseCharacter>(GetOwner()))
	{
		Mesh = Character->GetMesh();
	}
}

void UCharacterControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	HeadControl->Tick(DeltaTime);
	LeftHandControl->Tick(DeltaTime);
	RightHandControl->Tick(DeltaTime);
	PelvisControl->Tick(DeltaTime);
	LeftFootControl->Tick(DeltaTime);
	RightFootControl->Tick(DeltaTime);
}


void UCharacterControlComponent::MoveLeftHandTowards(FTransform TargetTransform, FBodyControlTargetReachedCallback OnTargetReached)
{
	FTransform currentTransform = Mesh->GetBoneTransform(FName("hand_l"));
	LeftHandControl->MoveTowards(
		currentTransform.GetLocation(), currentTransform.Rotator(), 
		TargetTransform.GetLocation(), TargetTransform.GetRotation().Rotator(), 
		OnTargetReached);
}

void UCharacterControlComponent::MoveRightHandTowards(FTransform TargetTransform, FBodyControlTargetReachedCallback OnTargetReached)
{
	FTransform currentTransform = Mesh->GetBoneTransform(FName("hand_r"));
	RightHandControl->MoveTowards(
		currentTransform.GetLocation(), currentTransform.Rotator(),
		TargetTransform.GetLocation(), TargetTransform.GetRotation().Rotator(),
		OnTargetReached);
}

void UCharacterControlComponent::Sit()
{
	IsSitting = true;
}

void UCharacterControlComponent::Stand()
{
	IsSitting = false;
	
	LeftHandControl->Data.IsControlled = false;
	RightHandControl->Data.IsControlled = false;
}

void UCharacterControlComponent::TurnHead(FRotator Rotator)
{
	HeadControl->RotateTowards(Rotator);
}

void UCharacterControlComponent::WatchRightHand()
{
	HeadControl->Data.IsControlled = false;
}
