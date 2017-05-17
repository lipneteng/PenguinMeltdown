// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "World/Triggers/PolarTrigger.h"
#include "PolarTrigger_SafeZone.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_MELTDOWN_API APolarTrigger_SafeZone : public APolarTrigger
{
	GENERATED_BODY()

		virtual void ActivateTrigger() override;

	UPROPERTY(EditAnywhere)
		TArray <FString> InfoMessages = { "You don't have penguins!" , "You have only one penguin!" , "Wrong colors!" };
};
