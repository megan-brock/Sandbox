#pragma once

#include "CoreMinimal.h"
#include "MealParticipant.h"
#include "Components/ActorComponent.h"
#include "ServerMealComponent.generated.h"

class UCustomerMealComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOrderReceived);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveCustomerChanged, UCustomerMealComponent*, NewCustomer);

UCLASS(Blueprintable)
class UServerMealComponent : public UMealParticipant
{
public:
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentCustomer(UCustomerMealComponent* NewCustomer);
	
public:
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	FOnActiveCustomerChanged OnActiveCustomerChanged;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default")
	TObjectPtr<UCustomerMealComponent> CurrentCustomer = nullptr;
};
