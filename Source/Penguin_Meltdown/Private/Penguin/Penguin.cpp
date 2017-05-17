// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Iceland.h"
#include "Penguin.h"


// Sets default values
APenguin::APenguin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APenguin::BeginPlay()
{
	Super::BeginPlay();

	int32 Limit = PenguinMap.Num();

	if (Limit > 0)
	{
		int32 Pick = FMath::RandRange(0, Limit - 1);

		TArray <USkeletalMesh*> MeshesArray;
		TArray <UAnimationAsset*> AnimationsArray;

		PenguinMap.GenerateKeyArray(MeshesArray);
		PenguinMap.GenerateValueArray(AnimationsArray);

		GetMesh()->SetSkeletalMesh(MeshesArray[Pick]);
		GetMesh()->PlayAnimation(AnimationsArray[Pick], true);
	}
}

// Called every frame
void APenguin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APenguin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APenguin::SetPenguinType(EPenguinType Type)
{
	PenguinType = Type;

	switch (PenguinType)
	{
	case EPenguinType::Green: GetMesh()->SetMaterial(1, GreenMaterial);
		break;
	case EPenguinType::Red: GetMesh()->SetMaterial(1, RedMaterial);
		break;
	case EPenguinType::Yellow: GetMesh()->SetMaterial(1, YellowMaterial);
		break;
	case EPenguinType::Blue: GetMesh()->SetMaterial(1, BlueMaterial);
		break;
	}
}

EPenguinType APenguin::GetPenguinType()
{
	return PenguinType;
}

bool APenguin::SetPolarControl(bool Control)
{
	if (Control)
	{
		AIceland* IcelandRef = CheckIcelandUnderPenguin();

		if (IcelandRef)
		{
			IcelandRef->SetActorOnIceland(nullptr);
			IcelandRef->SetState(EIcelandState::Free);
			bIsPolarControl = true;
			SetActorEnableCollision(false);
			return true;
		}
	}
	else
	{
		AIceland* IcelandRef = CheckIcelandUnderPenguin();

		if (IcelandRef)
		{
			IcelandRef->SetActorOnIceland(this);
			IcelandRef->SetState(EIcelandState::Penguin);
			bIsPolarControl = false;
			SetActorEnableCollision(true);
			SetActorLocation(IcelandRef->GetActorLocation() + FVector(0, 0, 50.0f));
			AttachToActor(IcelandRef, FAttachmentTransformRules::KeepWorldTransform);
			return true;
		}
	}

	return false;
}

AIceland* APenguin::CheckIcelandUnderPenguin()
{
	FHitResult Hit;

	FVector TraceStartLocation = GetActorLocation() + FVector(0, 0, 1000);
	FVector TraceEndLocation = GetActorLocation() - FVector(0, 0, 1000);

	FCollisionQueryParams TraceCollisionsParams;
	TraceCollisionsParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStartLocation, TraceEndLocation, ECollisionChannel::ECC_Visibility, TraceCollisionsParams);

	if (AIceland* IcelandRef = Cast<AIceland>(Hit.GetActor()))
	{
			return IcelandRef;
	}

	return nullptr;
}

bool APenguin::IsPolarControlled()
{
	return bIsPolarControl;
}