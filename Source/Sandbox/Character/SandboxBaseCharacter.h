#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterControlComponent.h"
#include "Logging/LogMacros.h"
#include "SandboxBaseCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

class UCharacterControlComponent;

UCLASS()
class ASandboxBaseCharacter : public ACharacter
{
public:
	GENERATED_BODY()
	
	ASandboxBaseCharacter();
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterControl)
	UCharacterControlComponent* CharacterControlComponent;
};
