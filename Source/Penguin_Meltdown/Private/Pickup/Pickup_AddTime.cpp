// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Pickup_AddTime.h"

void APickup_AddTime::TakePickup()
{
	AWorldKeeper* WorldKeeper = nullptr;
	UFunctionsLibrary::GetWorldKeeper(this, WorldKeeper);

	if (WorldKeeper)
	{
		WorldKeeper->AddGameTime(AddingTimeValue);
	}
}