// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "PolarTrigger.h"


APolarTrigger::APolarTrigger()
{
}

void APolarTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	PolarRef = Cast<APlayerPawn_Polar>(OtherActor);

	if (PolarRef)
	{
		ActivateTrigger();
	}
}

void APolarTrigger::ActivateTrigger()
{
}
