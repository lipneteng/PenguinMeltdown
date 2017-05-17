// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "IcelandGenerator.generated.h"

UCLASS()
class PENGUIN_MELTDOWN_API AIcelandGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIcelandGenerator();

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* DefaultScene;

	UPROPERTY(EditAnywhere)
		bool bIsGenerated = false;

	UPROPERTY(EditAnywhere)
		bool bClean = false;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AIceland> IcelandClass;

	UPROPERTY(EditAnywhere)
		int32 SizeX = 5;

	UPROPERTY(EditAnywhere)
		int32 SizeY = 10;

	UPROPERTY(EditAnywhere)
		float StepX = 100.0f;

	UPROPERTY(EditAnywhere)
		float StepY = 100.0f;

	UPROPERTY(EditAnywhere)
		float MeshSize = 1.0f;

	UPROPERTY(EditAnywhere)
		float TargetOffset = 100.0f;

	UPROPERTY(EditAnywhere)
		float IcelandSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <FVector> DefaultLocations;

	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Destroyed() override;

	void CleanIceland();

	UFUNCTION(BlueprintCallable, Category = "BlueprintCall")
		class AIceland* SpawnNewIceland(int32 NumberX);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	float X = 0.0f;
	float Y = 0.0f;
};
