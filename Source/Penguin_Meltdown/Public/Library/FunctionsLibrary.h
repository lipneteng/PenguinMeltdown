// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "IcelandGenerator.h"
#include "PenguinGenerator.h"
#include "EnemyGenerator.h"
#include "PlayerPawn_Polar.h"
#include "Penguin.h"
#include "WorldKeeper.h"
#include "FunctionsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_MELTDOWN_API UFunctionsLibrary : public UObject
{
	GENERATED_BODY()
		UFunctionsLibrary(const FObjectInitializer& ObjectInitializer);

public:

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Library")
		static void GetIcelandGenerator(UObject* WorldContextObject, AIcelandGenerator*& IcelandGenerator);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Library")
		static void GetPenguinGenerator(UObject* WorldContextObject, APenguinGenerator*& PenguinGenerator);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Library")
		static void GetEnemyGenerator(UObject* WorldContextObject, AEnemyGenerator*& EnemyGenerator);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Library")
		static void GetPlayerPawn_Polar(UObject* WorldContextObject, APlayerPawn_Polar*& Polar);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Library")
		static void GetWorldKeeper(UObject* WorldContextObject, AWorldKeeper*& WorldKeeper);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Library")
		static void GetCurrentIcelandsOnMap(UObject* WorldContextObject, TArray <AIceland*>& Icelands);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Library")
		static void GetCurrentPenguinsOnMap(UObject* WorldContextObject, TArray <APenguin*>& Penguins);

	UFUNCTION(BlueprintCallable, Category = "Library")
		static void ShuffleIcelandArr(TArray<AIceland*>& IcelandArr);
};
