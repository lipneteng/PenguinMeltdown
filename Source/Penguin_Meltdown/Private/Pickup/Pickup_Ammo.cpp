// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Pickup_Ammo.h"

void APickup_Ammo::TakePickup()
{
	Polar->IncBullets(BulletsInc);
}
