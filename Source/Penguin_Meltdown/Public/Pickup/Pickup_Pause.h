// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup/Pickup.h"
#include "Pickup_Pause.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_MELTDOWN_API APickup_Pause : public APickup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		float TimeUnderPause = 10.0f;

	virtual void TakePickup() override;
};
