// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Pickup_Power.h"

void APickup_Power::TakePickup()
{
	Polar->SetUnderPower(TimeUnderPower);
}