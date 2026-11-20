#include "SandboxAbilitySystemComponent.h"
#include "AbilityPromptInfo.h"
#include "SandboxAbility.h"

void USandboxAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	
	if (AbilityPromptInfoDataAsset && AbilitySpec.Ability)
	{
		FGameplayTag AbilityTag = AbilitySpec.Ability->GetAssetTags().First();
		FAbilityPromptInfo PromptInfo = AbilityPromptInfoDataAsset->GetAbilityPromptInfoByTag(AbilityTag);
		
		if (const USandboxAbility* SandboxAbility = Cast<USandboxAbility>(AbilitySpec.Ability))
		{
			PromptInfo = SandboxAbility->CustomizeAbilityPromptInfo(PromptInfo, AbilitySpec);
		}
		
		OnAbilityGranted.Broadcast(PromptInfo, AbilitySpec.Handle);
	}
}

void USandboxAbilitySystemComponent::OnRemoveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	OnAbilityRevoked.Broadcast(AbilitySpec.Handle);

	Super::OnRemoveAbility(AbilitySpec);
}

void USandboxAbilitySystemComponent::BroadcastExistingAbilities()
{
	// Lock the scope to safely iterate over activatable abilities
	FScopedAbilityListLock ActiveScopeLock(*this);
	
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilityPromptInfoDataAsset && AbilitySpec.Ability)
		{
			FGameplayTag AbilityTag = AbilitySpec.Ability->GetAssetTags().First();
			FAbilityPromptInfo PromptInfo = AbilityPromptInfoDataAsset->GetAbilityPromptInfoByTag(AbilityTag);
			OnAbilityGranted.Broadcast(PromptInfo, AbilitySpec.Handle);
		}
	}
}