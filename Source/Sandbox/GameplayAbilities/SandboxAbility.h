#pragma once

#include "Abilities/GameplayAbility.h"
#include "SandboxAbility.generated.h"

struct FAbilityPromptInfo;

UCLASS(Blueprintable)
class USandboxAbility : public UGameplayAbility
{
public:
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Abilities")
	FAbilityPromptInfo CustomizeAbilityPromptInfo(const FAbilityPromptInfo& DefaultPromptInfo, const FGameplayAbilitySpec& Spec) const;
};
