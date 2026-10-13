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


void UCharacterControlComponent::MoveLeftHandToLocation(FTransform TargetTransform)
{
	FTransform currentTransform = Mesh->GetBoneTransform(FName("hand_l"));
	LeftHandControl->MoveTowards(currentTransform.GetLocation(), currentTransform.Rotator(), TargetTransform.GetLocation(), TargetTransform.GetRotation().Rotator());
}

void UCharacterControlComponent::MoveRightHandToLocation(FTransform TargetTransform)
{
	FTransform currentTransform = Mesh->GetBoneTransform(FName("hand_r"));
	RightHandControl->MoveTowards(currentTransform.GetLocation(), currentTransform.Rotator(),TargetTransform.GetLocation(), TargetTransform.GetRotation().Rotator());
}

void UCharacterControlComponent::Sit(FTransform PelvisTargetTransform, FTransform LeftFootTargetTransform,
	FTransform RightFootTargetTransform)
{
	FTransform currentPelvisTransform = Mesh->GetBoneTransform(FName("pelvis"));
	FTransform currentLeftFootTransform = Mesh->GetBoneTransform(FName("foot_l"));
	FTransform currentRightFootTransform = Mesh->GetBoneTransform(FName("foot_r"));
	
	PelvisControl->MoveTowards(currentPelvisTransform.GetLocation(), currentPelvisTransform.Rotator(),PelvisTargetTransform.GetLocation(), PelvisTargetTransform.GetRotation().Rotator());
	LeftFootControl->MoveTowards(currentLeftFootTransform.GetLocation(), currentLeftFootTransform.Rotator(), LeftFootTargetTransform.GetLocation(), LeftFootTargetTransform.GetRotation().Rotator());
	RightFootControl->MoveTowards(currentRightFootTransform.GetLocation(), currentRightFootTransform.Rotator(), RightFootTargetTransform.GetLocation(), RightFootTargetTransform.GetRotation().Rotator());
}

void UCharacterControlComponent::Stand()
{
	PelvisControl->Data.IsControlled = false;
	LeftFootControl->Data.IsControlled = false;
	RightFootControl->Data.IsControlled = false;
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
