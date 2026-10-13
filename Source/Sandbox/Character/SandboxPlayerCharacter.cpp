#include "SandboxPlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

void ASandboxPlayerCharacter::NotifyControllerChanged()
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

void ASandboxPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASandboxPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ASandboxPlayerCharacter::Turn);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASandboxPlayerCharacter::Look);
		
		EnhancedInputComponent->BindAction(ControlHandAction, ETriggerEvent::Started, this, &ASandboxPlayerCharacter::StartControllingHand);
		EnhancedInputComponent->BindAction(ControlHandAction, ETriggerEvent::Completed, this, &ASandboxPlayerCharacter::StopControllingHand);
		EnhancedInputComponent->BindAction(MoveHandAction, ETriggerEvent::Triggered, this, &ASandboxPlayerCharacter::MoveHand);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASandboxPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	CharacterControlComponent->TurnHead(FRotator::ZeroRotator);
}

void ASandboxPlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller && CharacterControlComponent)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
		
		auto headYaw = CharacterControlComponent->HeadControl->Data.CurrentRotation.Yaw;
		AddControllerYawInput( headYaw / 90);
	}
}

void ASandboxPlayerCharacter::Turn(const FInputActionValue& Value)
{
	float RotationVector = Value.Get<float>();
	
	if (Controller)
	{
		AddControllerYawInput(RotationVector);
	}
}

void ASandboxPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Value2D = Value.Get<FVector2D>();
	
	FRotator HeadRotation = CharacterControlComponent->HeadControl->Data.CurrentRotation;
	HeadRotation.Pitch = 0.0f;
	HeadRotation.Yaw = FMath::Clamp(HeadRotation.Yaw + Value2D.X, -90.0f, 90.0f);
	HeadRotation.Roll = FMath::Clamp(HeadRotation.Roll + Value2D.Y, -90.0f, 70.0f);
	
	UE_LOG(LogTemplateCharacter, Warning, TEXT("Head Rotation: %s"), *HeadRotation.ToString());
	
	CharacterControlComponent->TurnHead(HeadRotation);
}

void ASandboxPlayerCharacter::StartControllingHand()
{
	if (!InputSubsystem)
	{
		return;
	}
	
	FTransform newRightHandTarget = GetMesh()->GetBoneTransform(FName("hand_r"));
	CharacterControlComponent->MoveRightHandToLocation(newRightHandTarget);
	
	InputSubsystem->AddMappingContext(MovingHandMappingContext, 2);
}

void ASandboxPlayerCharacter::StopControllingHand()
{
	if (!InputSubsystem)
	{
		return;
	}
	
	CharacterControlComponent->RightHandControl->Data.IsControlled = false;

	InputSubsystem->RemoveMappingContext(MovingHandMappingContext);

	CharacterControlComponent->TurnHead(FRotator::ZeroRotator);
}

void ASandboxPlayerCharacter::MoveHand(const FInputActionValue& Value)
{
	if (!CharacterControlComponent->RightHandControl->Data.IsControlled)
	{
		return;
	}
	
	FVector2D Value2D = Value.Get<FVector2D>();

	FTransform rightHandTransform = GetMesh()->GetBoneTransform(FName("hand_r"));
	FTransform rightShoulderTransform = GetMesh()->GetBoneTransform(FName("upperarm_r"));
	
	FRotator newRightHandRotation = (rightShoulderTransform.GetLocation() - rightHandTransform.GetLocation()).Rotation();
	newRightHandRotation.Pitch = 0.0f;
	newRightHandRotation.Roll = 90.0f;
	newRightHandRotation.Yaw *= 1.3f;
	
	FVector newRightHandLocation = CharacterControlComponent->RightHandControl->Data.CurrentLocation + GetActorForwardVector() * Value2D.Y + GetActorRightVector() * -Value2D.X;
	
	CharacterControlComponent->RightHandControl->SnapTo(newRightHandLocation, newRightHandRotation);
	CharacterControlComponent->WatchRightHand();
}

void ASandboxPlayerCharacter::EnterMealContext()
{
	if (!InputSubsystem)
	{
		return;
	}
	
	InputSubsystem->RemoveMappingContext(DefaultMappingContext);
	InputSubsystem->AddMappingContext(MealMappingContext, 1);
}

void ASandboxPlayerCharacter::ExitMealContext()
{
	if (!InputSubsystem)
	{
		return;
	}
	
	InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
	InputSubsystem->RemoveMappingContext(MealMappingContext);
	
	StopControllingHand();
}