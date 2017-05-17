// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Bound.h"


// Sets default values
ABound::ABound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultScene = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(DefaultScene);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	CollisionBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABound::BeginPlay()
{
	Super::BeginPlay();

	if (!IcelandGeneratorRef)
	{
		UFunctionsLibrary::GetIcelandGenerator(this, IcelandGeneratorRef);
	}

	if (!PenguinGeneratorRef)
	{
		UFunctionsLibrary::GetPenguinGenerator(this, PenguinGeneratorRef);
	}
}

// Called every frame
void ABound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABound::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (AIceland* IcelandRef = Cast<AIceland>(OtherActor))
	{
		if (IcelandGeneratorRef)
		{
			AIceland* NewIceland = IcelandGeneratorRef->SpawnNewIceland(IcelandRef->GetNumberXLine());
			if (IcelandRef->GetState() != EIcelandState::Free && IcelandRef->GetActorOnIceland())
			{
				IcelandRef->GetActorOnIceland()->Destroy();
			}

			IcelandRef->Destroy();
			IcelandArray.Add(NewIceland);

			if (IcelandArray.Num() == IcelandLimit && PenguinGeneratorRef)
			{
				PenguinGeneratorRef->SpawnPenguins(IcelandArray);
				IcelandArray.Empty();
			}
		}
	}
}
