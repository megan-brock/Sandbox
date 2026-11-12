#pragma once

#include "CoreMinimal.h"
#include "FoodType.h"
#include "GameFramework/Actor.h"
#include "Sandbox/Interaction/InteractableItemComponent.h"
#include "FoodItem.generated.h"

class UCustomerMealComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBite, UCustomerMealComponent*, Customer);

UCLASS(Blueprintable)
class AFoodItem : public AActor
{
public:
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodItem)
	EFoodType FoodType;

public:
	AFoodItem();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = FoodItem)
	void PlaceOnTable(FTransform TargetTransform);
	
	UFUNCTION(BlueprintCallable, Category = FoodItem)
	bool HasRemaining();
	
	UFUNCTION(BlueprintCallable, Category = FoodItem)
	bool RemovePortion();
	
	UFUNCTION(BlueprintCallable, Category = FoodItem)
	virtual void TakeBite(UCustomerMealComponent* Customer);

	UFUNCTION(BlueprintCallable, Category = FoodItem)
	bool TryCollect();
	
	UPROPERTY( BlueprintAssignable, Category = FoodItem)
	FOnFinished OnFinished;
	
	UPROPERTY( BlueprintAssignable, Category = FoodItem)
	FOnBite OnBite;

	UPROPERTY(BlueprintReadOnly, Category = FoodItem)
	FTransform OriginalTransform;
	
	UPROPERTY(BlueprintReadWrite, Category = FoodItem)
	FTransform OriginalInteractTransform;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
	UInteractableItemComponent* InteractableItemComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodItem)
	int BitesRemaining = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodItem)
	bool NeedsCollectionAfterFinishing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodItem)
	bool ReadyForCollection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodItem)
	bool Interactable = true;
};
