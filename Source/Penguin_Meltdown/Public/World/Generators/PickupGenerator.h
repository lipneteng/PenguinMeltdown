// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.h"
#include "PickupGenerator.generated.h"

UCLASS()
class PENGUIN_MELTDOWN_API APickupGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupGenerator();

	UPROPERTY(EditAnywhere)
		TArray <TSubclassOf<APickup>> PickupClasses;

	UPROPERTY(EditAnywhere)
		float SpawnDistanceLimit = 1000.0f;

	UPROPERTY(EditAnywhere)
		float SpawnHeight = 100.0f;

	UPROPERTY(EditAnywhere)
		float TimeToSpawn = 10.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	FTimerHandle SpawnTimerHandle;

	void SpawnPickup();
};
