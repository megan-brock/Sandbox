#include "SandboxAbility.h"
#include "AbilityPromptInfo.h"

FAbilityPromptInfo USandboxAbility::CustomizeAbilityPromptInfo_Implementation(
	const FAbilityPromptInfo& DefaultPromptInfo, const FGameplayAbilitySpec& Spec) const
{
	return DefaultPromptInfo;
}
