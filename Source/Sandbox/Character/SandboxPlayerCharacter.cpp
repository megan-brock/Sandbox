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
}

void ASandboxPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASandboxPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ASandboxPlayerCharacter::Turn);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASandboxPlayerCharacter::Look);
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

	UE_LOG(LogTemplateCharacter, Warning, TEXT("MovementVector: %s"), *MovementVector.ToString());
	
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
	
	CharacterControlComponent->TurnHead(HeadRotation);
}

void ASandboxPlayerCharacter::MoveHand(const FVector2D& Value, const FVector& Offset)
{	
	FVector newRightHandLocation = 
		CharacterControlComponent->RightHandControl->Data.CurrentLocation + 
			GetActorForwardVector() * Value.Y + 
				GetActorRightVector() * -Value.X;

	FTransform rightHandTransform = GetMesh()->GetBoneTransform(FName("hand_r"), RTS_Actor);
	FTransform rightShoulderTransform = GetMesh()->GetBoneTransform(FName("upperarm_r"), RTS_Actor);
	
	FRotator newRightHandRotation = (rightShoulderTransform.GetLocation() - rightHandTransform.GetLocation()).Rotation();
	newRightHandRotation = GetActorTransform().TransformRotation(newRightHandRotation.Quaternion()).Rotator();
	newRightHandRotation.Pitch = 0.0f;
	newRightHandRotation.Roll = 90.0f;
	
	if (Offset != FVector::ZeroVector)
	{
		newRightHandLocation.Z = Offset.Z + 5.0f;
	}
	
	UE_LOG(LogTemplateCharacter, Warning, TEXT("newRightHandLocation: %s"), *newRightHandLocation.ToString());
	
	CharacterControlComponent->RightHandControl->SnapTo(newRightHandLocation, newRightHandRotation);
	CharacterControlComponent->WatchRightHand();
}
