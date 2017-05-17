// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class PENGUIN_MELTDOWN_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* MyScene;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* BulletMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* ProjectileMoveComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	
	
};
