// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Penguin.h"
#include "Iceland.h"
#include "PenguinGenerator.generated.h"

USTRUCT(BlueprintType)
struct FPenguinSpawnTemplate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		int32 Count = 5;

	UPROPERTY(EditAnywhere)
		float ProbGreen = 60;

	UPROPERTY(EditAnywhere)
		float ProbRed = 20;

	UPROPERTY(EditAnywhere)
		float ProbYellow = 15;

	UPROPERTY(EditAnywhere)
		float ProbBlue = 5;
};

UCLASS()
class PENGUIN_MELTDOWN_API APenguinGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APenguinGenerator();

	UPROPERTY(EditAnywhere)
		FPenguinSpawnTemplate PenguinSpawnTemplate;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APenguin> PenguinClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnPenguins(TArray<AIceland*>& IcelandArr);

private:
	EPenguinType CalculateChance(float Dice);
};
