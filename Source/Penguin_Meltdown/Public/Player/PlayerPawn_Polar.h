// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Penguin.h"
#include "PlayerPawn_Polar.generated.h"

//#define TestTracing

UCLASS()
class PENGUIN_MELTDOWN_API APlayerPawn_Polar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerPawn_Polar();

	//Bullets and gun
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class USkeletalMeshComponent* Gun;

	UPROPERTY(EditAnywhere)
		TSubclassOf <class ABullet> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 BulletsNum = 10;

	//Penguins
	UPROPERTY(EditAnywhere)
		float PenguinTakeRadius = 100.0f;

	UPROPERTY(EditAnywhere)
		int32 PenguinLimit = 2;

	//Power mod
	UPROPERTY(BlueprintReadWrite)
		bool bIsUnderPower = false;

	UPROPERTY(BlueprintReadWrite)
		float TimeUnderPower = 0.0f;

	//Speed
	UPROPERTY(EditAnywhere)
		float DefaultSpeed = 400.0f;

	//Dead
	UPROPERTY(EditAnywhere)
		FVector DefaultLocation = FVector::ZeroVector;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Power mod
	FTimerHandle UnderPowerTimer;

	void CalculateTimeUnderPower(float DeltaSeconds);

	//Speed
	void UpdateSpeed();

	//Bullets and gun
	void DecBullets();

	//Penguins
	TArray <APenguin*> CurrentPenguins;

	bool CheckNearPenguin(APenguin*& PenguinRef);
	FName GetPenguinSocket();

public:
	//Control 
	void Attack();

	//Penguins
	void TakePenguin();
	void UnTakePenguin();

	void ClearPenguins();
	void ClearPenguinSpecific(APenguin* PenguinRef);

	UFUNCTION(BlueprintCallable, Category = "BlueprintCall")
	TArray <APenguin*> GetPenguinsArray();

	//Pickup mod
	void SetUnderPower(float TimeUnderPower);
	void IncBullets(int32 BulletsValue);

	//Dead
	void SetDefaultLocation();

	//Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFireIsStarted);

	UPROPERTY(BlueprintAssignable)
		FFireIsStarted OnFireIsStarted;

};
