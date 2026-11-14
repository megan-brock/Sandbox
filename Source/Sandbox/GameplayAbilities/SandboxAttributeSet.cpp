#include "SandboxAttributeSet.h"

USandboxAttributeSet::USandboxAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
	
	InitStamina(100.0f);
	InitMaxStamina(100.0f);
}

void USandboxAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
		OnHealthChanged.Broadcast(NewValue);
	}

	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
		OnStaminaChanged.Broadcast(NewValue);
	}
}

void USandboxAttributeSet::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(GetHealth());
	OnMaxHealthChanged.Broadcast(GetMaxHealth());
	OnStaminaChanged.Broadcast(GetStamina());
	OnMaxStaminaChanged.Broadcast(GetMaxStamina());
}