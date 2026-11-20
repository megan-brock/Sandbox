#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CharacterControlComponent.h"
#include "Logging/LogMacros.h"
#include "SandboxBaseCharacter.generated.h"

class USandboxAbilitySystemComponent;
struct FGameplayTag;
class USandboxAttributeSet;
class UCharacterControlComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ASandboxBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
public:
	GENERATED_BODY()
	
	ASandboxBaseCharacter();
	
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	void OnBlockInputTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterControl)
	TObjectPtr<UCharacterControlComponent> CharacterControlComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<USandboxAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<USandboxAttributeSet> AttributeSet;
	
private:
	FDelegateHandle BlockInputTagHandle;
};
