// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Iceland.h"
#include "FunctionsLibrary.h"
#include "Bound.generated.h"

UCLASS()
class PENGUIN_MELTDOWN_API ABound : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABound();

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* DefaultScene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
		class AIcelandGenerator* IcelandGeneratorRef;

	UPROPERTY(EditAnywhere)
		class APenguinGenerator* PenguinGeneratorRef;

	UPROPERTY(EditAnywhere)
		int32 IcelandLimit = 10;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	TArray <AIceland*> IcelandArray;
};
