// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "World/Triggers/PolarTrigger.h"
#include "PolarTrigger_DeadZone.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_MELTDOWN_API APolarTrigger_DeadZone : public APolarTrigger
{
	GENERATED_BODY()

		virtual void ActivateTrigger() override;
};
