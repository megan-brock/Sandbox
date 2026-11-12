#pragma once

#include "CoreMinimal.h"
#include "MealParticipant.generated.h"

class AMealAreaManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFoodAreaChanged, AMealAreaManager*, MealAreaManager);

UCLASS(Blueprintable)
class UMealParticipant : public UActorComponent
{
public:
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void EnterMealArea(AMealAreaManager* AreaManager);
	
	UFUNCTION(BlueprintCallable)
	void LeaveMealArea();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	bool AutoRegister;

	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	FOnFoodAreaChanged OnFoodAreaChanged;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="Default")
	AMealAreaManager* MealAreaManager = nullptr;
};