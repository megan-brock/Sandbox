#pragma once
#include "AbilitySystemComponent.h"
#include "SandboxAbilitySystemComponent.generated.h"

class UAbilityPromptInfoDataAsset;
struct FAbilityPromptInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnAbilityGranted, 
	FAbilityPromptInfo, PromptInfo, 
	FGameplayAbilitySpecHandle, AbilitySpecHandle);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnAbilityRevoked, 
	FGameplayAbilitySpecHandle, AbilitySpecHandle);

UCLASS()
class USandboxAbilitySystemComponent : public UAbilitySystemComponent
{
public:
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Abilities")
	FOnAbilityGranted OnAbilityGranted;

	UPROPERTY(BlueprintAssignable, Category = "Abilities")
	FOnAbilityRevoked OnAbilityRevoked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TObjectPtr<UAbilityPromptInfoDataAsset> AbilityPromptInfoDataAsset;

public:
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void BroadcastExistingAbilities();
	
protected:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRemoveAbility(FGameplayAbilitySpec& AbilitySpec) override;
};
