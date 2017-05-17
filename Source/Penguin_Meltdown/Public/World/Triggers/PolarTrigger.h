// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerBox.h"
#include "FunctionsLibrary.h"
#include "PolarTrigger.generated.h"

UCLASS()
class PENGUIN_MELTDOWN_API APolarTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:

	APolarTrigger();

protected:
	APlayerPawn_Polar* PolarRef = nullptr;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void ActivateTrigger();	
};
