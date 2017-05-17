// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "InfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_MELTDOWN_API UInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		FString Message;
};
