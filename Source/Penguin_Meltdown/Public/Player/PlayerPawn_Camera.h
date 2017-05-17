// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PlayerPawn_Polar.h"
#include "PlayerPawn_Camera.generated.h"

UCLASS()
class PENGUIN_MELTDOWN_API APlayerPawn_Camera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn_Camera();

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* DefaultScene;

	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		class APlayerPawn_Polar* PolarRef;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//Movement and action func

	void MovePolarForward(float Value);
	void MovePolarRight(float Value);

	void JumpPolar();

	void TakePolar();
	void UnTakePolar();

	void AttackPolar();
	
	
};
