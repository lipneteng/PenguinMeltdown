// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "FunctionsLibrary.h"


UFunctionsLibrary::UFunctionsLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UFunctionsLibrary::GetIcelandGenerator(UObject* WorldContextObject, AIcelandGenerator*& IcelandGenerator)
{
	TArray <AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, AIcelandGenerator::StaticClass(), Actors);

	if (Actors.Num() > 0)
	{
		IcelandGenerator = Cast<AIcelandGenerator>(Actors[0]);
	}
}

void UFunctionsLibrary::GetPenguinGenerator(UObject* WorldContextObject, APenguinGenerator*& PenguinGenerator)
{
	TArray <AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, APenguinGenerator::StaticClass(), Actors);

	if (Actors.Num() > 0)
	{
		PenguinGenerator = Cast<APenguinGenerator>(Actors[0]);
	}
}

void UFunctionsLibrary::GetEnemyGenerator(UObject* WorldContextObject, AEnemyGenerator*& EnemyGenerator)
{
	TArray <AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, AEnemyGenerator::StaticClass(), Actors);

	if (Actors.Num() > 0)
	{
		EnemyGenerator = Cast<AEnemyGenerator>(Actors[0]);
	}
}


void UFunctionsLibrary::GetPlayerPawn_Polar(UObject* WorldContextObject, APlayerPawn_Polar*& Polar)
{
	TArray <AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, APlayerPawn_Polar::StaticClass(), Actors);

	if (Actors.Num() > 0)
	{
		Polar = Cast<APlayerPawn_Polar>(Actors[0]);
	}
}

void UFunctionsLibrary::GetWorldKeeper(UObject* WorldContextObject, AWorldKeeper*& WorldKeeper)
{
	TArray <AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, AWorldKeeper::StaticClass(), Actors);

	if (Actors.Num() > 0)
	{
		WorldKeeper = Cast<AWorldKeeper>(Actors[0]);
	}
}

void UFunctionsLibrary::GetCurrentIcelandsOnMap(UObject* WorldContextObject, TArray<AIceland *> & Icelands)
{
	TArray <AActor*> Actors;
	TArray <AIceland* > IcelandsTempArr;

	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, AIceland::StaticClass(), Actors);

	if (Actors.Num() > 0)
	{
		for (int32 i = 0; i < Actors.Num(); i++)
		{
			if (AIceland* IcelandRef = Cast<AIceland>(Actors[i]))
			{
				IcelandsTempArr.Add(IcelandRef);
			}
		}
	}

	Icelands = IcelandsTempArr;
}

void UFunctionsLibrary::GetCurrentPenguinsOnMap(UObject* WorldContextObject, TArray<APenguin *> & Penguins)
{
	TArray <AActor*> Actors;
	TArray <APenguin* > PenguinsTempArr;

	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, APenguin::StaticClass(), Actors);

	if (Actors.Num() > 0)
	{
		for (int32 i = 0; i < Actors.Num(); i++)
		{
			if (APenguin* PenguinRef = Cast<APenguin>(Actors[i]))
			{
				PenguinsTempArr.Add(PenguinRef);
			}
		}
	}

	Penguins = PenguinsTempArr;
}

void UFunctionsLibrary::ShuffleIcelandArr(TArray<AIceland *>& IcelandArr)
{
	if (IcelandArr.Num())
	{
		int32 LastIndex = IcelandArr.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(0, LastIndex);
			if (i != Index)
			{
				IcelandArr.Swap(i, Index);
			}
		}
	}
}
