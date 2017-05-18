// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Kismet/KismetMathLibrary.h"
#include "Bullet.h"
#include "PlayerPawn_Polar.h"


// Sets default values
APlayerPawn_Polar::APlayerPawn_Polar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Gun = CreateDefaultSubobject<USkeletalMeshComponent>("Gun");
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "GunSocket");

	StepsSoundComponent = CreateDefaultSubobject<UAudioComponent>("StepsSound");
	StepsSoundComponent->SetActive(false);
}

// Called when the game starts or when spawned
void APlayerPawn_Polar::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPawn_Polar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayStepsSound();

	CalculateTimeUnderPower(DeltaTime);
}

void APlayerPawn_Polar::PlayStepsSound()
{
	float Velocity = 0.0f;
	Velocity = GetCharacterMovement()->Velocity.Size();

	if (Velocity == 0)
	{
		StepsSoundComponent->SetActive(false);
	}

	else
	{
		StepsSoundComponent->SetActive(true);
	}
}

// Called to bind functionality to input
void APlayerPawn_Polar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn_Polar::TakePenguin()
{
	APenguin* PenguinRef = nullptr;

	if (CurrentPenguins.Num() < PenguinLimit && CheckNearPenguin(PenguinRef))
	{
		if (PenguinRef->SetPolarControl(true))
		{
			CurrentPenguins.Add(PenguinRef);

			FName SocketName = GetPenguinSocket();
			FVector SocketLocation = GetMesh()->GetSocketLocation(SocketName);

			PenguinRef->SetActorLocation(SocketLocation);
			PenguinRef->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform, SocketName);

			UpdateSpeed();
		}
	}
}

bool APlayerPawn_Polar::CheckNearPenguin(APenguin* & PenguinRef)
{
	FHitResult Hit;

	FVector TraceStartLocation = GetActorLocation();
	FVector TraceEndLocation = TraceStartLocation + FVector(0, 0, 1);

	float TraceSphereRadius = PenguinTakeRadius;

	FCollisionObjectQueryParams TraceCollisionObjectParams;
	TraceCollisionObjectParams.AddObjectTypesToQuery(ECC_Pawn);

	FCollisionQueryParams TraceCollisionParams;
	TraceCollisionParams.AddIgnoredActor(this);

#ifdef TestTracing
	TraceCollisionParams.TraceTag = "TraceTag";
	UWorld* World = GetWorld();
	World->DebugDrawTraceTag = "TraceTag";
#endif

	GetWorld()->SweepSingleByObjectType(Hit, TraceStartLocation, TraceEndLocation, FQuat(), TraceCollisionObjectParams, FCollisionShape::MakeSphere(TraceSphereRadius), TraceCollisionParams);

	if (APenguin* PenguinCastActor = Cast<APenguin>(Hit.GetActor()))
	{
		PenguinRef = PenguinCastActor;
		return true;
	}

	return false;
}

FName APlayerPawn_Polar::GetPenguinSocket()
{
	int32 SocketNumber = CurrentPenguins.Num();
	FName SocketName;

	switch (SocketNumber)
	{
	case 1: SocketName = "Penguin1";
		break;
	case 2: SocketName = "Penguin2";
		break;
	}

	return SocketName;
}

void APlayerPawn_Polar::UpdateSpeed()
{
	float Speed = 0.0f;

	if (!bIsUnderPower)
	{
		int32 PenguinNum = CurrentPenguins.Num();

		switch (PenguinNum)
		{
		case 0: Speed = DefaultSpeed;
			break;
		case 1: Speed = DefaultSpeed / 2;
			break;
		case 2: Speed = DefaultSpeed / 4;
			break;
		}

		GetCharacterMovement()->MaxWalkSpeed = Speed;
	}

	else
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	}
}

void APlayerPawn_Polar::UnTakePenguin()
{
	if (CurrentPenguins.Num() > 0)
	{
		APenguin* PenguinRef = CurrentPenguins[CurrentPenguins.Num() - 1];
		if (PenguinRef->SetPolarControl(false))
		{
			CurrentPenguins.Remove(PenguinRef);
			UpdateSpeed();
		}
	}
}

void APlayerPawn_Polar::SetDefaultLocation()
{
	SetActorLocation(DefaultLocation);
	ClearPenguins();
}

void APlayerPawn_Polar::ClearPenguins()
{
	if (CurrentPenguins.Num() > 0)
	{
		for (int32 i = 0; i < CurrentPenguins.Num(); i++)
		{
			CurrentPenguins[i]->Destroy();
		}

		CurrentPenguins.Empty();
	}

	UpdateSpeed();
}

void APlayerPawn_Polar::ClearPenguinSpecific(APenguin* PenguinRef)
{
	CurrentPenguins.Remove(PenguinRef);
	PenguinRef->Destroy();

	UpdateSpeed();
}

TArray <APenguin*> APlayerPawn_Polar::GetPenguinsArray()
{
	return CurrentPenguins;
}

void APlayerPawn_Polar::SetUnderPower(float TimeUnderPower)
{
	if (!bIsUnderPower)
	{
		bIsUnderPower = true;
		this->TimeUnderPower = TimeUnderPower;
		UpdateSpeed();
	}
}

void APlayerPawn_Polar::CalculateTimeUnderPower(float DeltaSeconds)
{
	if (bIsUnderPower)
	{
		TimeUnderPower -= DeltaSeconds;
		if (TimeUnderPower <= 0.0f)
		{
			TimeUnderPower = 0.0f;
			bIsUnderPower = false;
			UpdateSpeed();
		}
	}
}

void APlayerPawn_Polar::IncBullets(int32 BulletsValue)
{
	BulletsNum += BulletsValue;
}

void APlayerPawn_Polar::DecBullets()
{
	BulletsNum--;
}

void APlayerPawn_Polar::Attack()
{
	if (BulletClass && BulletsNum > 0)
	{
		APlayerController* PC;
		FVector MouseLocation;
		FVector MouseDirection;
		FRotator RotateTo;

		PC = UGameplayStatics::GetPlayerController(this, 0);
		PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

		MouseDirection *= (MouseLocation.Z / MouseDirection.Z) * -1;
		MouseLocation += MouseDirection;

		RotateTo = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MouseLocation);
		RotateTo = FRotator(GetActorRotation().Pitch, RotateTo.Yaw, GetActorRotation().Roll);

		SetActorRotation(RotateTo);

		GetWorld()->SpawnActor<ABullet>(BulletClass, Gun->GetSocketLocation("Muzzle"), RotateTo);
		MakeAttackSound();
		DecBullets();

		OnFireIsStarted.Broadcast();
	}
}

void APlayerPawn_Polar::MakeAttackSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, AttackSound, Gun->GetSocketLocation("Muzzle"));
}