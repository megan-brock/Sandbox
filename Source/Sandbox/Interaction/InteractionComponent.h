#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class FInteractableDroppedCallback;
class FInteractablePickedUpCallback;
class UInteractableItemComponent;
class UCharacterControlComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void Pickup(UInteractableItemComponent* Item, bool UseLeftHand, FInteractablePickedUpCallback ItemPickedUpCallback);

	UFUNCTION(BlueprintCallable)
	void Drop(UInteractableItemComponent* Item, bool UseLeftHand, FInteractableDroppedCallback ItemDroppedCallback);
	
	UPROPERTY(BlueprintReadOnly)
	TArray<UInteractableItemComponent*> HeldItems;
	
private:
	UPROPERTY()
	TObjectPtr<UCharacterControlComponent> ControlComponent;
};
