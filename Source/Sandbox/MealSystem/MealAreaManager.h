#pragma once

#include "CoreMinimal.h"
#include "MealAreaManager.generated.h"

class UMealParticipant;
class IMealParticipant;
class UServerMealComponent;
class UCustomerMealComponent;

UCLASS(Blueprintable)
class AMealAreaManager : public AActor
{
public:
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Register(UMealParticipant* MealParticipant);

	UFUNCTION(BlueprintCallable)
	void MatchServersToCustomers();

	UFUNCTION(BlueprintCallable)
	void Unregister(UMealParticipant* MealParticipant);

	UFUNCTION(BlueprintCallable)
	bool IsRegistered(UMealParticipant* MealParticipant);
	
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TArray<UCustomerMealComponent*> WaitingCustomers;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TArray<UServerMealComponent*> AvailableFoodServers;
};
