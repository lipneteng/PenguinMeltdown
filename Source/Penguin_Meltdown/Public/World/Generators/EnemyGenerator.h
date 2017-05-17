// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Seal.h"
#include "EnemyGenerator.generated.h"

UCLASS()
class PENGUIN_MELTDOWN_API AEnemyGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyGenerator();

	UPROPERTY(EditAnywhere)
		float TimeForFirstSpawn = 10.0f;

	UPROPERTY(EditAnywhere)
		float TimeForNewSpawn = 10.0f;

	/*For test func
	UPROPERTY(EditAnywhere)
		int32 SealLimit = 1;
	*/

	UPROPERTY(EditAnywhere)
		float SealMovementSpeed = 200.0f;

	UPROPERTY(EditAnywhere)
		float DistanceEdge = 1000.0f;

	UPROPERTY(EditAnywhere)
		float RandomStepX = 100.0f;

	UPROPERTY(EditAnywhere)
		float RandomStepY = 100.0f;

	UPROPERTY(EditAnywhere)
		TSubclassOf <ASeal> SealClass;

	FTimerHandle SpawnTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ClearEnemyAndSpawnNew(ASeal* Seal);
	
private:
	TArray <ASeal*> CurrentSeals;

	void SpawnEnemy();

	AIceland* GetNearestIcelandToPolar();
};
