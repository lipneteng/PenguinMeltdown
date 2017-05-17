// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Kismet/KismetMathLibrary.h"
#include "Iceland.h"
#include "IcelandGenerator.h"


// Sets default values
AIcelandGenerator::AIcelandGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultScene = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(DefaultScene);
}

// Called when the game starts or when spawned
void AIcelandGenerator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AIcelandGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIcelandGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (bIsGenerated && IcelandClass)
	{
		CleanIceland();
		DefaultLocations.Empty();
		X = 0;
		Y = 0;

		for (int32 i = 0; i < SizeY; i++)
		{
			for (int32 j = 0; j < SizeX; j++)
			{
				FVector SpawnLocation = GetActorLocation() + FVector(X, Y, 0.0f);
				FRotator SpawnRotation = FRotator(0.0f, UKismetMathLibrary::RandomFloatInRange(0.0f, 360.0f), 0.0f);
				FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation, UKismetMathLibrary::Conv_FloatToVector(MeshSize));

				AIceland* IcelandRef = GetWorld()->SpawnActor<AIceland>(IcelandClass, SpawnTransform);

				IcelandRef->SetSpeed(IcelandSpeed);
				IcelandRef->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				IcelandRef->SetNumberXLine(j);

				//UGameplayStatics::FinishSpawningActor(IcelandRef, SpawnTransform);
				UE_LOG(LogTemp, Warning, TEXT("Speed is : %f"), IcelandRef->GetSpeed());

				X += StepX;

				if (i == 0)
				{
					DefaultLocations.Add(IcelandRef->GetActorLocation() + FVector(0,TargetOffset,0));
				}
			}

			X = 0;
			Y += StepY;
		}
	}

	if (bClean)
	{
		CleanIceland();
		bClean = false;
		bIsGenerated = false;
	}
}

void AIcelandGenerator::Destroyed()
{
	CleanIceland();
}

void AIcelandGenerator::CleanIceland()
{
	TArray <AActor*> Actors;
	GetAttachedActors(Actors);

	for (int32 i = 0; i < Actors.Num(); i++)
	{
		if (Actors[i])
		{
			Actors[i]->Destroy();
		}
	}
}

AIceland* AIcelandGenerator::SpawnNewIceland(int32 NumberX)
{
	FVector SpawnLocation = DefaultLocations[NumberX];
	FRotator SpawnRotation = FRotator(0.0f, UKismetMathLibrary::RandomFloatInRange(0.0f, 360.0f), 0.0f);
	FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation, UKismetMathLibrary::Conv_FloatToVector(MeshSize));

	AIceland* IcelandRef = GetWorld()->SpawnActor<AIceland>(IcelandClass, SpawnTransform);

	IcelandRef->SetSpeed(IcelandSpeed);
	IcelandRef->SetNumberXLine(NumberX);

	return IcelandRef;
}