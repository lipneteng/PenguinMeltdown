// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Seal.generated.h"

UCLASS()
class PENGUIN_MELTDOWN_API ASeal : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASeal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void KillSeal();

	const bool IsDead();

private:
	bool bIsDead = false;

	FTimerHandle DeadTimer;

	void OnKilled();
};
