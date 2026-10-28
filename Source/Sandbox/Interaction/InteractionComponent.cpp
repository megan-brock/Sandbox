#include "InteractionComponent.h"
#include "InteractableItemComponent.h"
#include "GameFramework/Character.h"
#include "Sandbox/Character/CharacterControlComponent.h"

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (AActor* Owner = GetOwner())
	{
		ControlComponent = Owner->FindComponentByClass<UCharacterControlComponent>();
	}
	
	if (!ControlComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s could not find UCharacterControlComponent on owning actor."), *GetName());
	}
}

void UInteractionComponent::Pickup(UInteractableItemComponent* Item, bool UseLeftHand, FInteractablePickedUpCallback InteractablePickedUpCallback)
{
	ACharacter* InteractingCharacter = Cast<ACharacter>(GetOwner());
	Item->PickedUpCallback = InteractablePickedUpCallback;
	Item->SetInteractingCharacter(InteractingCharacter);
	
	FBodyControlTargetReachedCallback ItemReachedCallback;
	ItemReachedCallback.BindDynamic(Item, &UInteractableItemComponent::HandleItemReached);
	
	FVector ReturnLocation;
	FRotator ReturnRotation;
	Item->GetReturnLocationAndRotation(ReturnLocation, ReturnRotation);
	
	ReturnLocation += FVector(0.0f, 0.0f, 5.0f);
	
	UBodyControl* HandControl = UseLeftHand ? ControlComponent->LeftHandControl : ControlComponent->RightHandControl;
	HandControl->MoveTowards(ReturnLocation, ReturnRotation, ItemReachedCallback, FBodyControlTargetCancelledCallback());
	
	HeldItems.Add(Item);
}

void UInteractionComponent::Drop(UInteractableItemComponent* Item, bool UseLeftHand, FInteractableDroppedCallback ItemDroppedCallback)
{
	Item->DroppedCallback = ItemDroppedCallback;

	FBodyControlTargetReachedCallback ItemReturnReachedCallback;
	ItemReturnReachedCallback.BindDynamic(Item, &UInteractableItemComponent::HandleItemReturnReached);
	
	FVector ReturnLocation;
	FRotator ReturnRotation;
	Item->GetReturnLocationAndRotation(ReturnLocation, ReturnRotation);
	
	UBodyControl* HandControl = UseLeftHand ? ControlComponent->LeftHandControl : ControlComponent->RightHandControl;
	HandControl->MoveTowards(ReturnLocation, ReturnRotation, ItemReturnReachedCallback, FBodyControlTargetCancelledCallback());
	
	HeldItems.Remove(Item);
}
