// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "SealAIController.h"
#include "FunctionsLibrary.h"
#include "Seal.h"


// Sets default values
ASeal::ASeal()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ASealAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ASeal::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASeal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASeal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASeal::KillSeal()
{
	if (!bIsDead)
	{
		bIsDead = true;
		GetCharacterMovement()->StopMovementImmediately();
		GetMesh()->SetSimulatePhysics(true);
		GetWorld()->GetTimerManager().SetTimer(DeadTimer, this, &ASeal::OnKilled, 2.0f, false);
	}
}

void ASeal::OnKilled()
{
	AEnemyGenerator* EnemyGenerator;
	UFunctionsLibrary::GetEnemyGenerator(this, EnemyGenerator);

	if (EnemyGenerator)
	{
		EnemyGenerator->ClearEnemyAndSpawnNew(this);
		Destroy();
	}
}

const bool ASeal::IsDead()
{
	return bIsDead;
}
