#include "SandboxBaseCharacter.h"
#include "CharacterControlComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ASandboxBaseCharacter::ASandboxBaseCharacter()
{
	CharacterControlComponent = CreateDefaultSubobject<UCharacterControlComponent>(TEXT("CharacterControlComponent"));
}
