// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyControl.h"
#include "Components/ActorComponent.h"
#include "CharacterControlComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDBOX_API UCharacterControlComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UCharacterControlComponent();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = CharacterControl)
	TObjectPtr<UBodyControl> HeadControl;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = CharacterControl)
	TObjectPtr<UBodyControl> LeftHandControl;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = CharacterControl)
	TObjectPtr<UBodyControl> RightHandControl;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = CharacterControl)
	TObjectPtr<UBodyControl> PelvisControl;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = CharacterControl)
	TObjectPtr<UBodyControl> LeftFootControl;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = CharacterControl)
	TObjectPtr<UBodyControl> RightFootControl;
	
public:
	UFUNCTION(BlueprintCallable, Category = CharacterControl)
	void MoveLeftHandToLocation(FTransform TargetPosition);
	
	UFUNCTION(BlueprintCallable, Category = CharacterControl)
	void MoveRightHandToLocation(FTransform TargetPosition);

	UFUNCTION(BlueprintCallable, Category = CharacterControl)
	void Sit(FTransform PelvisTargetTransform, FTransform LeftFootTargetTransform, FTransform RightFootTargetTransform);
	
	UFUNCTION(BlueprintCallable, Category = CharacterControl)
	void Stand();
	
	UFUNCTION(BlueprintCallable, Category = CharacterControl)
	void TurnHead(FRotator Rotator);
	
	UFUNCTION(BlueprintCallable, Category = CharacterControl)
	void WatchRightHand();
	
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> Mesh;
};
