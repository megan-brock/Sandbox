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
	TObjectPtr<UBodyControl> LeftHandControl;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = CharacterControl)
	TObjectPtr<UBodyControl> RightHandControl;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterControl)
	bool IsSitting;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterControl)
	FRotator HeadRotationTarget;
	
public:
	UFUNCTION(BlueprintCallable, Category = CharacterControl)
	void Sit();
	
	UFUNCTION(BlueprintCallable, Category = CharacterControl)
	void Stand();
	
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> Mesh;
};
