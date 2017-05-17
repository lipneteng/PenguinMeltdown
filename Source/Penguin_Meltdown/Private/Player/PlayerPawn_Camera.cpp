// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "FunctionsLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerPawn_Camera.h"


// Sets default values
APlayerPawn_Camera::APlayerPawn_Camera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(DefaultScene);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetWorldRotation(FRotator(-50.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APlayerPawn_Camera::BeginPlay()
{
	Super::BeginPlay();

	if (!PolarRef)
	{
		UFunctionsLibrary::GetPlayerPawn_Polar(this, PolarRef);
	}
	
}

// Called every frame
void APlayerPawn_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn_Camera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerPawn_Camera::MovePolarForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerPawn_Camera::MovePolarRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerPawn_Camera::JumpPolar);
	PlayerInputComponent->BindAction("Hook", IE_Pressed, this, &APlayerPawn_Camera::TakePolar);
	PlayerInputComponent->BindAction("CancelHook", IE_Pressed, this, &APlayerPawn_Camera::UnTakePolar);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerPawn_Camera::AttackPolar);
}

void APlayerPawn_Camera::MovePolarForward(float Value)
{
	FRotator PawnRotation = GetControlRotation();
	PawnRotation = FRotator(0, PawnRotation.Yaw, 0);

	FVector Direction = UKismetMathLibrary::GetForwardVector(PawnRotation);

	if (PolarRef)
	{
		PolarRef->AddMovementInput(Direction, Value);
	}
}

void APlayerPawn_Camera::MovePolarRight(float Value)
{
	FRotator PawnRotation = GetControlRotation();
	PawnRotation = FRotator(0, PawnRotation.Yaw, 0);

	FVector Direction = UKismetMathLibrary::GetRightVector(PawnRotation);

	if (PolarRef)
	{
		PolarRef->AddMovementInput(Direction, Value);
	}
}

void APlayerPawn_Camera::JumpPolar()
{
	if (PolarRef)
	{
		PolarRef->Jump();
	}
}

void APlayerPawn_Camera::TakePolar()
{
	if (PolarRef)
	{
		PolarRef->TakePenguin();
	}
}

void APlayerPawn_Camera::UnTakePolar()
{
	if (PolarRef)
	{
		PolarRef->UnTakePenguin();
	}
}

void APlayerPawn_Camera::AttackPolar()
{
	if (PolarRef)
	{
		PolarRef->Attack();
	}
}