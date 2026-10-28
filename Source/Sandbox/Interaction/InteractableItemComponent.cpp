#include "InteractableItemComponent.h"
#include "GameFramework/Character.h"
#include "Sandbox/Character/BodyControl.h"

void UInteractableItemComponent::SetInteractingCharacter(ACharacter* Character)
{
	InteractingCharacter = Character;
}

void UInteractableItemComponent::BeginPlay()
{
	Super::BeginPlay();

	OriginalTransform = GetOwner()->GetTransform();
	
	if (ReturnTransformComponent)
	{
		OriginalTransform += ReturnTransformComponent->GetComponentTransform();
	}
}

void UInteractableItemComponent::Pickup(bool UseLeftHand)
{
	AActor* Owner = GetOwner();
	if (!Owner || !InteractingCharacter || !InteractingCharacter->GetMesh())
	{
		UE_LOG(LogTemp, Warning, TEXT("Pickup failed: missing owner, interacting character, or character mesh."));
		return;
	}
	
	FName SocketName = UseLeftHand ? FName(TEXT("hand_lSocket")) : FName(TEXT("hand_rSocket"));
	Owner->AttachToComponent(InteractingCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	
	if (ReturnTransformComponent)
	{
		FTransform ReturnTransform = ReturnTransformComponent->GetRelativeTransform();
		ReturnTransform.SetScale3D(FVector::OneVector);

		Owner->SetActorRelativeTransform(ReturnTransform.Inverse());
	}
}

void UInteractableItemComponent::Drop()
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Drop failed: missing owner."));
		return;
	}

	Owner->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Owner->SetActorTransform(OriginalTransform, false, nullptr, ETeleportType::TeleportPhysics);
}

void UInteractableItemComponent::GetReturnLocationAndRotation(FVector& Location, FRotator& Rotation)
{
	Location = OriginalTransform.GetLocation();
	Rotation = OriginalTransform.Rotator();
}

void UInteractableItemComponent::HandleItemReached(UBodyControl* BodyControl)
{
	if (!BodyControl)
	{
		UE_LOG(LogTemp, Warning, TEXT("HandleItemReached failed: BodyControl is null."));
		return;
	}

	bool bUseLeftHand = BodyControl->Data.BoneName == FName(TEXT("hand_l"));
	Pickup(bUseLeftHand);
	PickedUpCallback.ExecuteIfBound(this, BodyControl);
}

void UInteractableItemComponent::HandleItemReturnReached(UBodyControl* BodyControl)
{
	if (!BodyControl)
	{
		UE_LOG(LogTemp, Warning, TEXT("HandleItemReturnReached failed: BodyControl is null."));
		return;
	}

	Drop();
	DroppedCallback.ExecuteIfBound(this, BodyControl);
}
