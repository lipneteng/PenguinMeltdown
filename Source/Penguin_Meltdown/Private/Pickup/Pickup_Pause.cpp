// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Pickup_Pause.h"

void APickup_Pause::TakePickup()
{
	AWorldKeeper* WorldKeeper = nullptr;
	UFunctionsLibrary::GetWorldKeeper(this, WorldKeeper);

	if (WorldKeeper)
	{
		WorldKeeper->SetPauseTime(TimeUnderPause);
	}
}
