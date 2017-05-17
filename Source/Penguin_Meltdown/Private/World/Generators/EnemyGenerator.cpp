// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "FunctionsLibrary.h"
#include "EnemyGenerator.h"


// Sets default values
AEnemyGenerator::AEnemyGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyGenerator::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemyGenerator::SpawnEnemy, TimeForFirstSpawn, false);
}

// Called every frame
void AEnemyGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyGenerator::SpawnEnemy()
{
	AIceland* IcelandRef = GetNearestIcelandToPolar();
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	if (SealClass && IcelandRef)
	{
		FVector IcelandLocation = IcelandRef->GetActorLocation();

		SpawnLocation = FVector(IcelandLocation.X + FMath::RandRange(-RandomStepX, RandomStepX), IcelandLocation.Y + FMath::RandRange(-RandomStepY, RandomStepY), IcelandLocation.Z + 100.0f);

		ASeal* SealRef = GetWorld()->SpawnActor<ASeal>(SealClass, SpawnLocation, SpawnRotation);

		SealRef->GetCharacterMovement()->MaxWalkSpeed = SealMovementSpeed;

		CurrentSeals.Add(SealRef);
	}
}

AIceland* AEnemyGenerator::GetNearestIcelandToPolar()
{
	TArray <AIceland* > Icelands;
	AIceland* IcelandRef = nullptr;

	APlayerPawn_Polar* PolarRef = nullptr;

	UFunctionsLibrary::GetCurrentIcelandsOnMap(this, Icelands);
	UFunctionsLibrary::GetPlayerPawn_Polar(this, PolarRef);

	if (!PolarRef || Icelands.Num() == 0)
	{
		return nullptr;
	}

	UFunctionsLibrary::ShuffleIcelandArr(Icelands);

	for (int32 i = 0; i < Icelands.Num(); i++)
	{
		IcelandRef = Icelands[i];

		if (IcelandRef && IcelandRef->GetState() == EIcelandState::Free)
		{
			float Distance = (IcelandRef->GetActorLocation() - PolarRef->GetActorLocation()).Size();

			if (Distance <= DistanceEdge)
			{
				return IcelandRef;
			}

		}
	}

	return nullptr;
}

void AEnemyGenerator::ClearEnemyAndSpawnNew(ASeal* Seal)
{
	CurrentSeals.Remove(Seal);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemyGenerator::SpawnEnemy, TimeForNewSpawn, false);
}