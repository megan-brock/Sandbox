#pragma once

#include "CoreMinimal.h"
#include "FoodType.h"
#include "GameFramework/Actor.h"
#include "FoodItem.generated.h"

class UMealParticipantComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBite, UMealParticipantComponent*, MealParticipant);

UCLASS(Blueprintable)
class AFoodItem : public AActor
{
public:
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodItem)
	EFoodType FoodType;
	
public:
	UFUNCTION(BlueprintCallable, Category = FoodItem)
	void PlaceOnTable(FTransform TargetTransform);
	
	UFUNCTION(BlueprintCallable, Category = FoodItem)
	bool HasRemaining();
	
	UFUNCTION(BlueprintCallable, Category = FoodItem)
	bool RemovePortion();
	
	UFUNCTION(BlueprintCallable, Category = FoodItem)
	virtual void TakeBite(UMealParticipantComponent* MealParticipant);
	
	UFUNCTION(BlueprintCallable, Category = FoodItem)
	void ResetPosition();
	
	UFUNCTION(BlueprintCallable, Category = FoodItem)
	bool TryCollect();
	
	UPROPERTY( BlueprintAssignable, Category = FoodItem)
	FOnFinished OnFinished;
	
	UPROPERTY( BlueprintAssignable, Category = FoodItem)
	FOnBite OnBite;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodItem)
	int BitesRemaining = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodItem)
	bool NeedsCollectionAfterFinishing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodItem)
	bool ReadyForCollection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoodItem)
	bool Interactable = true;
	
	FTransform OriginalTransform;
};
