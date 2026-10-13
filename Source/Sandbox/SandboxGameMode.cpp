// Copyright Epic Games, Inc. All Rights Reserved.

#include "SandboxGameMode.h"
#include "UObject/ConstructorHelpers.h"

ASandboxGameMode::ASandboxGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Sandbox/Character/BP_SandboxCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
