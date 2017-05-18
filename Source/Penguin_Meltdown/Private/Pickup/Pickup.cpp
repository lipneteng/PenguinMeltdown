// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(DefaultScene);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ColBox"));
	CollisionBox->SetupAttachment(DefaultScene);
	CollisionBox->SetBoxExtent(FVector(40.0f, 40.0f, 40.0f));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CollisionBox);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("StaticMesh'/Game/Assets/Pickups/SM_Bonus.SM_Bonus'"));
	if (MeshRef.Object)
	{
		Mesh->SetStaticMesh(MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundTakingRef(TEXT("SoundWave'/Game/Audio/Pickups/S_Bonus.S_Bonus'"));
	if (SoundTakingRef.Object)
	{
		TakingSound = SoundTakingRef.Object;
	}

	Mesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -35.0f));
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (APlayerPawn_Polar* Polar = Cast<APlayerPawn_Polar>(OtherActor))
	{
		TakePickup();
		MakeTakingSound();
		Destroy();
	}
}

void APickup::TakePickup()
{
}

void APickup::MakeTakingSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, TakingSound, GetActorLocation());
}