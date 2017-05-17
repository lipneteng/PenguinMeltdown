// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FunctionsLibrary.h"
#include "Pickup.generated.h"


UCLASS()
class PENGUIN_MELTDOWN_API APickup : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APickup();

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* DefaultScene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY()
		APlayerPawn_Polar* Polar = nullptr;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void TakePickup();

};
