#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SandboxAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedEvent, float, NewValue);

UCLASS(BlueprintType)
class USandboxAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	USandboxAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USandboxAttributeSet, Health)

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChangedEvent OnHealthChanged;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USandboxAttributeSet, MaxHealth)

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChangedEvent OnMaxHealthChanged;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina;
	
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChangedEvent OnStaminaChanged;
	ATTRIBUTE_ACCESSORS(USandboxAttributeSet, Stamina)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(USandboxAttributeSet, MaxStamina)
	
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChangedEvent OnMaxStaminaChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void BroadcastInitialValues();
	
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};