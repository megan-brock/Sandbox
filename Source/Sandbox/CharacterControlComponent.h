// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterControlComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDBOX_API UCharacterControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterControlComponent();

	UFUNCTION(BlueprintCallable, Category = Input)
	bool GetIsSitting() const;
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetIsSitting(const bool NewIsSitting);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterControl)
	bool IsControllingHand;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterControl)
	FRotator HeadBoneRotation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterControl)
	FTransform LeftHandTarget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterControl)
	FTransform RightHandTarget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterControl)
	FTransform PelvisTarget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterControl)
	FTransform LeftFootTarget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterControl)
	FTransform RightFootTarget;

private:	
	bool IsSitting;
};
