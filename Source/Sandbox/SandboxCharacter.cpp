// Copyright Epic Games, Inc. All Rights Reserved.

#include "SandboxCharacter.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ASandboxCharacter::ASandboxCharacter()
{
	CharacterControlComponent = CreateDefaultSubobject<UCharacterControlComponent>(TEXT("CharacterControlComponent"));
	InputSubsystem = nullptr;
}

void ASandboxCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// CharacterControlComponent->HeadRotationTarget = FRotator(90.0f, 0.0f, 0.0f);
}

void ASandboxCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			InputSubsystem = Subsystem;
		}
	}
	
	InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
}

void ASandboxCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			InputSubsystem = Subsystem;
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASandboxCharacter::Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ASandboxCharacter::Turn);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASandboxCharacter::Look);
		
		EnhancedInputComponent->BindAction(ControlHandAction, ETriggerEvent::Started, this, &ASandboxCharacter::StartControllingHand);
		EnhancedInputComponent->BindAction(ControlHandAction, ETriggerEvent::Completed, this, &ASandboxCharacter::StopControllingHand);
		EnhancedInputComponent->BindAction(MoveHandAction, ETriggerEvent::Triggered, this, &ASandboxCharacter::MoveHand);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASandboxCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller && CharacterControlComponent)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
		
		auto headRotationTarget = CharacterControlComponent->HeadBoneRotation.Euler();
		AddControllerYawInput( headRotationTarget.Z / 90);
	}
}

void ASandboxCharacter::Turn(const FInputActionValue& Value)
{
	float RotationVector = Value.Get<float>();
	
	if (Controller)
	{
		AddControllerYawInput(RotationVector);
	}
}

void ASandboxCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Value2D = Value.Get<FVector2D>();
	
	FRotator HeadRotation = CharacterControlComponent->HeadBoneRotation;

	HeadRotation.Pitch = FMath::Clamp(HeadRotation.Pitch - Value2D.X, -90.0f, 90.0f);
	HeadRotation.Yaw = FMath::Clamp(HeadRotation.Yaw + Value2D.Y, -60.0f, 60.0f);
	HeadRotation.Roll = 0.0f;

	CharacterControlComponent->HeadBoneRotation = HeadRotation;

	UE_LOG(
		LogTemplateCharacter,
		Warning,
		TEXT("HeadBoneRotationTarget: Pitch=%f, Yaw=%f, Roll=%f"),
		HeadRotation.Pitch,
		HeadRotation.Yaw,
		HeadRotation.Roll
	);
}

void ASandboxCharacter::StartControllingHand()
{
	if (!InputSubsystem)
	{
		return;
	}
	
	CharacterControlComponent->IsControllingHand = true;
	
	InputSubsystem->AddMappingContext(MovingHandMappingContext, 2);
	
	// CharacterControlComponent->HeadRotationTarget = FRotator::ZeroRotator;
	// CharacterControlComponent->RightHandTarget = GetMesh()->GetSocketTransform(FName("hand_rSocket")); 
}

void ASandboxCharacter::StopControllingHand()
{
	if (!InputSubsystem)
	{
		return;
	}

	CharacterControlComponent->IsControllingHand = false;

	InputSubsystem->RemoveMappingContext(MovingHandMappingContext);
	
	// CharacterControlComponent->RightHandTarget = FTransform::Identity;
}

void ASandboxCharacter::MoveHand(const FInputActionValue& Value)
{
	if (!CharacterControlComponent->IsControllingHand)
	{
		return;
	}
	
	FVector2D Value2D = Value.Get<FVector2D>();
	
	FTransform newRightHandTarget = CharacterControlComponent->RightHandTarget;
	newRightHandTarget.AddToTranslation(GetActorForwardVector() * Value2D.Y + GetActorRightVector() * -Value2D.X);
	
	CharacterControlComponent->RightHandTarget = newRightHandTarget;
}

void ASandboxCharacter::EnterMealContext()
{
	if (!InputSubsystem)
	{
		return;
	}
	
	CharacterControlComponent->SetIsSitting(true);
	InputSubsystem->RemoveMappingContext(DefaultMappingContext);
	InputSubsystem->AddMappingContext(MealMappingContext, 1);
}

void ASandboxCharacter::ExitMealContext()
{
	if (!InputSubsystem)
	{
		return;
	}
	
	CharacterControlComponent->SetIsSitting(false);
	InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
	InputSubsystem->RemoveMappingContext(MealMappingContext);
	
	StopControllingHand();
}