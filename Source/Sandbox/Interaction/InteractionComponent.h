#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class FInteractableDroppedCallback;
class FInteractablePickedUpCallback;
class UInteractableItemComponent;
class UCharacterControlComponent;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void Pickup(UInteractableItemComponent* Item, UBodyControl* HandControl, FInteractablePickedUpCallback ItemPickedUpCallback);

	UFUNCTION(BlueprintCallable)
	void Drop(UInteractableItemComponent* Item, UBodyControl* HandControl, FInteractableDroppedCallback ItemDroppedCallback);
	
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UInteractableItemComponent>> HeldItems;

protected:
	UPROPERTY(Blueprintable, BlueprintReadOnly, EditAnywhere, Category = Interaction)
	TObjectPtr<UCharacterControlComponent> ControlComponent;
};
