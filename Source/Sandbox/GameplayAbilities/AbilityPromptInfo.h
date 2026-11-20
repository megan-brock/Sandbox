#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "AbilityPromptInfo.generated.h"

USTRUCT(BlueprintType)
struct FAbilityPromptInfo
{
public:
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText PromptText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UTexture2D> AbilityIcon = nullptr;
};

UCLASS(BlueprintType)
class UAbilityPromptInfoDataAsset : public UDataAsset
{
public:
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TArray<FAbilityPromptInfo> AbilityInformation;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	FAbilityPromptInfo GetAbilityPromptInfoByTag(const FGameplayTag& AbilityTag) const;
};