// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup/Pickup.h"
#include "Pickup_Ammo.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_MELTDOWN_API APickup_Ammo : public APickup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		int32 BulletsInc = 5;

	virtual void TakePickup() override;
};
