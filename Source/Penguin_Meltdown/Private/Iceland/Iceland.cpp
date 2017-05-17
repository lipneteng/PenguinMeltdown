// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "FunctionsLibrary.h"
#include "Iceland.h"


// Sets default values
AIceland::AIceland()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(DefaultScene);

	IcelandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IcelandMesh"));
	IcelandMesh->SetupAttachment(DefaultScene);
}


// Called when the game starts or when spawned
void AIceland::BeginPlay()
{
	Super::BeginPlay();

	AWorldKeeper* WorldKeeperRef = nullptr;
	UFunctionsLibrary::GetWorldKeeper(this, WorldKeeperRef);

	if (WorldKeeperRef)
	{
		WorldKeeperRef->OnTimeIsPaused.AddDynamic(this, &AIceland::BindOnTimeIsPaused);
		WorldKeeperRef->OnTimeIsNotPausedNow.AddDynamic(this, &AIceland::BindOnTimeIsNotPausedNow);
	}
}

// Called every frame
void AIceland::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveToBorder(DeltaTime);
}

void AIceland::MoveToBorder(float Delta)
{
	FVector Direction = FVector(0.0f, 1.0f, 0.0f);
	FVector NewLocation = GetActorLocation() + Direction * GetSpeed() * Delta;

	UE_LOG(LogTemp, Warning, TEXT("Speed is : %f"), GetSpeed());
	SetActorLocation(NewLocation);
}

void AIceland::SetSpeed(float SpeedValue) 
{ 
	Speed = SpeedValue;
}

const float AIceland::GetSpeed()
{
	return Speed;
}

void AIceland::SetState(EIcelandState NewState)
{
	State = NewState;
}

const EIcelandState AIceland::GetState()
{
	return State;
}

void AIceland::SetActorOnIceland(AActor* ActorRef)
{
	ActorOnIceland = ActorRef;
}

AActor* AIceland::GetActorOnIceland()
{
	return ActorOnIceland;
}

void AIceland::SetNumberXLine(int32 NumXLine)
{
	NumberXLine = NumXLine;
}

const int32 AIceland::GetNumberXLine()
{ 
	return NumberXLine; 
}

void AIceland::BindOnTimeIsPaused(float TimeDilValue)
{
	CustomTimeDilation = TimeDilValue;
}

void AIceland::BindOnTimeIsNotPausedNow()
{
	CustomTimeDilation = 1.0f;
}