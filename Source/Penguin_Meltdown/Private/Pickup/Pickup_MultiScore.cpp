// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Pickup_MultiScore.h"

void APickup_MultiScore::TakePickup()
{
	AWorldKeeper* WorldKeeper = nullptr;
	UFunctionsLibrary::GetWorldKeeper(this, WorldKeeper);

	if (WorldKeeper)
	{
		WorldKeeper->SetMultiScoreTime(TimeUnderMultiScore);
	}
}
