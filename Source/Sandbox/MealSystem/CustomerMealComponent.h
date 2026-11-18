#pragma once

#include "CoreMinimal.h"
#include "MealParticipant.h"
#include "Components/ActorComponent.h"
#include "CustomerMealComponent.generated.h"

class UServerMealComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveServerChanged, UServerMealComponent*, NewServer);

UCLASS(Blueprintable)
class UCustomerMealComponent : public UMealParticipant
{
public:
	GENERATED_BODY()
	
	void SetCurrentServer(UServerMealComponent* NewServer);
	
public:
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	FOnActiveServerChanged OnActiveServerChanged;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default")
	TObjectPtr<UServerMealComponent> CurrentServer = nullptr;
};
