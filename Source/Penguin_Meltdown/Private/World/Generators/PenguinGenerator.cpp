// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "FunctionsLibrary.h"
#include "PenguinGenerator.h"


// Sets default values
APenguinGenerator::APenguinGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APenguinGenerator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APenguinGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APenguinGenerator::SpawnPenguins(TArray<AIceland*>& IcelandArr)
{
	float RandDice = 0;

	EPenguinType PenguinType = EPenguinType::Green;
	AIceland* IcelandRef = nullptr;

	for (int32 i = 0; i < PenguinSpawnTemplate.Count; i++)
	{
		UFunctionsLibrary::ShuffleIcelandArr(IcelandArr);

		RandDice = FMath::RandRange(0.0f, 100.0f);
		PenguinType = CalculateChance(RandDice);

		for (int32 j = 0; j < IcelandArr.Num() - 1; j++)
		{
			IcelandRef = IcelandArr[j];

			if (IcelandRef && IcelandRef->GetState() == EIcelandState::Free)
			{
				APenguin* PenguinRef = GetWorld()->SpawnActor<APenguin>(PenguinClass, IcelandRef->GetActorLocation() + FVector(0,0,50.0f), FRotator(0,0,0));

				PenguinRef->AttachToActor(IcelandRef, FAttachmentTransformRules::KeepWorldTransform);
				PenguinRef->SetPenguinType(PenguinType);
				IcelandRef->SetState(EIcelandState::Penguin);
				IcelandRef->SetActorOnIceland(PenguinRef);

				break;
			}
		}
	}
}

EPenguinType APenguinGenerator::CalculateChance(float Dice)
{
	float LeftDice = PenguinSpawnTemplate.ProbGreen;

	if (Dice >= 0.0 && Dice < LeftDice) return EPenguinType::Green;
	if (Dice >= LeftDice && Dice < LeftDice + PenguinSpawnTemplate.ProbRed) return EPenguinType::Red;
	LeftDice += PenguinSpawnTemplate.ProbRed;
	if (Dice >= LeftDice && Dice < LeftDice + PenguinSpawnTemplate.ProbYellow) return EPenguinType::Yellow;
	LeftDice += PenguinSpawnTemplate.ProbYellow;
	if (Dice >= LeftDice) return EPenguinType::Blue;

	//if bad then
	UE_LOG(LogTemp, Error, TEXT("Error spawn"));
	return EPenguinType::Green;
}