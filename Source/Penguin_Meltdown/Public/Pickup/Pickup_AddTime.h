// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup/Pickup.h"
#include "Pickup_AddTime.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_MELTDOWN_API APickup_AddTime : public APickup
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
		float AddingTimeValue = 10.0f;

		virtual void TakePickup() override;
};
