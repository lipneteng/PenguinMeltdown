// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "FunctionsLibrary.h"
#include "PickupGenerator.h"


// Sets default values
APickupGenerator::APickupGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APickupGenerator::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APickupGenerator::SpawnPickup, TimeToSpawn, true);
}

// Called every frame
void APickupGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupGenerator::SpawnPickup()
{
	TArray <AIceland*> Icelands;

	UFunctionsLibrary::GetCurrentIcelandsOnMap(this, Icelands);
	UFunctionsLibrary::ShuffleIcelandArr(Icelands);

	for (int32 i = 0; i < Icelands.Num(); i++)
	{
		AIceland* IcelandRef = Icelands[i];

		APlayerPawn_Polar* Polar = nullptr;
		UFunctionsLibrary::GetPlayerPawn_Polar(this, Polar);

		if (IcelandRef && Polar && IcelandRef->GetState() == EIcelandState::Free && (IcelandRef->GetActorLocation() - Polar->GetActorLocation()).Size() < SpawnDistanceLimit)
		{
			int32 Index = FMath::RandRange(0, PickupClasses.Num() - 1);

			FVector SpawnLocation = IcelandRef->GetActorLocation() + FVector(0, 0, SpawnHeight);
			FRotator SpawnRotation = FRotator(0, 0, 0);

			APickup* PickupRef = GetWorld()->SpawnActor<APickup>(PickupClasses[Index], SpawnLocation, SpawnRotation);

			if (PickupRef)
			{
				PickupRef->AttachToActor(IcelandRef, FAttachmentTransformRules::KeepWorldTransform);
				IcelandRef->SetState(EIcelandState::Pickup);
				IcelandRef->SetActorOnIceland(PickupRef);

				return;
			}
		}
	}
}
