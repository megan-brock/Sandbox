#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableItemComponent.generated.h"

class ACharacter;
class UBodyControl;
class UInteractableItemComponent;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FInteractablePickedUpCallback, UInteractableItemComponent*, Interactable, UBodyControl*, BodyControl);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FInteractableDroppedCallback, UInteractableItemComponent*, Interactable, UBodyControl*, BodyControl);

UCLASS(BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UInteractableItemComponent : public UActorComponent
{
public:
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void Pickup(bool UseLeftHand);

	UFUNCTION()
	void SetInteractingCharacter(ACharacter* Character);
	
	UFUNCTION()
	void Drop();

	UFUNCTION()
	void GetReturnLocationAndRotation(FVector& Location, FRotator& Rotation);
	
	UFUNCTION()
	void HandleItemReached(UBodyControl* BodyControl);
	
	UFUNCTION()
	void HandleItemReturnReached(UBodyControl* BodyControl);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	TObjectPtr<USceneComponent> ReturnTransformComponent;
	
	UPROPERTY()
	FInteractablePickedUpCallback PickedUpCallback;
	
	UPROPERTY()
	FInteractableDroppedCallback DroppedCallback;
	
	UPROPERTY()
	ACharacter* InteractingCharacter = nullptr;
	
	UPROPERTY()
	FTransform OriginalTransform;
};
