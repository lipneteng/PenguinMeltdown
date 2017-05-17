// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Seal.h"
#include "Bullet.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyScene = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(MyScene);
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("Bullet");
	BulletMesh->SetupAttachment(RootComponent);
	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("UProjectileMovementComponent");
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (ASeal* SealRef = Cast<ASeal>(OtherActor))
	{
		SealRef->KillSeal();
	}
}
