#include "AbilityPromptInfo.h"

FAbilityPromptInfo UAbilityPromptInfoDataAsset::GetAbilityPromptInfoByTag(const FGameplayTag& AbilityTag) const
{
	for (const FAbilityPromptInfo& info : AbilityInformation)
	{
		if (info.AbilityTag.MatchesTagExact(AbilityTag))
		{
			return info;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Can't find AbilityPromptInfo for Tag [%s]"), *AbilityTag.ToString());
	
	return FAbilityPromptInfo();
}
