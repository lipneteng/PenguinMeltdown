// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Penguin.h"
#include "PolarTrigger_SafeZone.h"


void APolarTrigger_SafeZone::ActivateTrigger()
{
	TArray <APenguin*> Penguins = PolarRef->GetPenguinsArray();

	AWorldKeeper* WorldKeeper;
	UFunctionsLibrary::GetWorldKeeper(this, WorldKeeper);

	if (!WorldKeeper)
	{
		return;
	}

	switch (Penguins.Num())
	{
			case 0:
			{
				WorldKeeper->AddInfoMessageOnScreen(InfoMessages[0]);
			}
			break;

			case 1:
			{
				WorldKeeper->AddInfoMessageOnScreen(InfoMessages[1]);
			}
			break;

			case 2:
			{
				if (Penguins[0]->GetPenguinType() == Penguins[1]->GetPenguinType())
				{
					EPenguinType PenguinsType = Penguins[0]->GetPenguinType();
					WorldKeeper->AddScorePoints(PenguinsType);
					MakeScoreSound();

					PolarRef->ClearPenguins();
				}
				else
				{
					WorldKeeper->AddInfoMessageOnScreen(InfoMessages[2]);
				}
			}
			break;
	}
}

void APolarTrigger_SafeZone::MakeScoreSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, ScoreSound, GetActorLocation());
}

