#pragma once

#include "CoreMinimal.h"
#include "MealParticipant.h"
#include "Components/ActorComponent.h"
#include "CustomerMealComponent.generated.h"

class UServerMealComponent;

UCLASS(Blueprintable)
class UCustomerMealComponent : public UMealParticipant
{
public:
	GENERATED_BODY()
	
	void SetCurrentServer(UServerMealComponent* NewServer);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default")
	TObjectPtr<UServerMealComponent> CurrentServer = nullptr;
};
