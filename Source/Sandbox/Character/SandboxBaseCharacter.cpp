#include "SandboxBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "CharacterControlComponent.h"
#include "Sandbox/SandboxGameplayTags.h"
#include "Sandbox/GameplayAbilities/SandboxAbilitySystemComponent.h"
#include "Sandbox/GameplayAbilities/SandboxAttributeSet.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ASandboxBaseCharacter::ASandboxBaseCharacter()
{
	CharacterControlComponent = CreateDefaultSubobject<UCharacterControlComponent>(TEXT("CharacterControlComponent"));
	AbilitySystemComponent = CreateDefaultSubobject<USandboxAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<USandboxAttributeSet>(TEXT("AttributeSet"));
}

void ASandboxBaseCharacter::BeginPlay()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	
	BlockInputTagHandle = AbilitySystemComponent->RegisterGameplayTagEvent(
			SandboxGameplayTags::State_BlockInput,
			EGameplayTagEventType::NewOrRemoved
		).AddUObject(this, &ASandboxBaseCharacter::OnBlockInputTagChanged);
	
	Super::BeginPlay();
}

void ASandboxBaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (AbilitySystemComponent && BlockInputTagHandle.IsValid())
	{
		AbilitySystemComponent->RegisterGameplayTagEvent(
			SandboxGameplayTags::State_BlockInput, 
			EGameplayTagEventType::NewOrRemoved
			).Remove(BlockInputTagHandle);
			
		BlockInputTagHandle.Reset();	
	}
}

UAbilitySystemComponent* ASandboxBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASandboxBaseCharacter::OnBlockInputTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	const bool bShouldBlockInput = NewCount > 0;

	Controller->SetIgnoreMoveInput(bShouldBlockInput);
	Controller->SetIgnoreLookInput(bShouldBlockInput);	
}
