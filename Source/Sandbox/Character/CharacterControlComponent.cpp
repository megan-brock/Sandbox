#include "CharacterControlComponent.h"
#include "SandboxBaseCharacter.h"

UCharacterControlComponent::UCharacterControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	LeftHandControl = CreateDefaultSubobject<UBodyControl>(TEXT("LeftHandControl"));
	LeftHandControl->Data.BoneName = FName("hand_l");
	
	RightHandControl = CreateDefaultSubobject<UBodyControl>(TEXT("RightHandControl"));
	RightHandControl->Data.BoneName = FName("hand_r");
}

void UCharacterControlComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (ASandboxBaseCharacter* Character = Cast<ASandboxBaseCharacter>(GetOwner()))
	{
		Mesh = Character->GetMesh();
		LeftHandControl->Mesh = Mesh;
		RightHandControl->Mesh = Mesh;
	}
}

void UCharacterControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	LeftHandControl->Tick(DeltaTime);
	RightHandControl->Tick(DeltaTime);
}

void UCharacterControlComponent::Sit()
{
	IsSitting = true;
}

void UCharacterControlComponent::Stand()
{
	IsSitting = false;
	
	LeftHandControl->Data.IsUserControlled = false;
	RightHandControl->Data.IsUserControlled = false;
	
	LeftHandControl->Data.IsControlled = false;
	RightHandControl->Data.IsControlled = false;
	
	LeftHandControl->Data.RestLocation = FVector::ZeroVector;
	LeftHandControl->Data.RestRotation = FRotator::ZeroRotator;
	
	RightHandControl->Data.RestLocation = FVector::ZeroVector;
	RightHandControl->Data.RestRotation = FRotator::ZeroRotator;
}
