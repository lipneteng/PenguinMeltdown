// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "Penguin.h"
#include "InfoWidget.h"
#include "EndGameMessageWidget.h"
#include "WorldKeeper.h"


// Sets default values
AWorldKeeper::AWorldKeeper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ScoreMap.Add("Green", 100);
	ScoreMap.Add("Red", 200);
	ScoreMap.Add("Yellow", 500);
	ScoreMap.Add("Blue", 1000);
}

// Called when the game starts or when spawned
void AWorldKeeper::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWorldKeeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateTime(DeltaTime);
}

void AWorldKeeper::AddScorePoints(EPenguinType PenguinsType)
{
	switch (PenguinsType)
	{
	case EPenguinType::Green: Score += *ScoreMap.Find("Green") * CurrentScoreMod;
		break;
	case EPenguinType::Red: Score += *ScoreMap.Find("Red") * CurrentScoreMod;
		break;
	case EPenguinType::Yellow: Score += *ScoreMap.Find("Yellow") * CurrentScoreMod;
		break;
	case EPenguinType::Blue: Score += *ScoreMap.Find("Blue") * CurrentScoreMod;
		break;
	}

	FString ScoreString = FString::FromInt(Score);
	FString ScoreMessage = "Your score is: ";

	ScoreMessage.Append(ScoreString);

	AddInfoMessageOnScreen(ScoreMessage);
}

void AWorldKeeper::SetPauseTime(float TimeUnderPause)
{
	if (!bIsUnderPause)
	{
		bIsUnderPause = true;
		this->TimeUnderPause = TimeUnderPause;

		OnTimeIsPaused.Broadcast(TimeDilationMod);
	}
}

void AWorldKeeper::CalculateTime(float DeltaSeconds)
{
	if (bIsGameEnded)
	{
		return;
	}

	GameTimeSeconds -= DeltaSeconds;

	if (GameTimeSeconds <= 0)
	{
		bIsGameEnded = true;
		AddEndMessageOnScreen();
	}

	if (bIsUnderPause)
	{
		TimeUnderPause -= DeltaSeconds;
		if (TimeUnderPause <= 0.0f)
		{
			TimeUnderPause = 0.0f;
			bIsUnderPause = false;
			OnTimeIsNotPausedNow.Broadcast();
		}
	}

	if (bIsUnderMultiScore)
	{
		TimeUnderMultiScore -= DeltaSeconds;
		if (TimeUnderMultiScore <= 0.0f)
		{
			TimeUnderMultiScore = 0.0f;
			bIsUnderMultiScore = false;
			CurrentScoreMod = DefaultScoreMod;
		}
	}
}

void AWorldKeeper::SetMultiScoreTime(float TimeUnderMultiScore)
{
	if (!bIsUnderMultiScore)
	{
		this->TimeUnderMultiScore = TimeUnderMultiScore;
		bIsUnderMultiScore = true;
		CurrentScoreMod = ScoreMod;
	}
}

void AWorldKeeper::AddGameTime(float ValueSeconds)
{
	GameTimeSeconds += ValueSeconds;
}

void AWorldKeeper::AddInfoMessageOnScreen(FString Message)
{
	if (!InfoWidgetClass)
	{
		return;
	}

	if (CheckMessageOnScreen())
	{
		ClearMessageOnScreen();
	}

	UInfoWidget* InfoRef = CreateWidget<UInfoWidget>(GetWorld(), InfoWidgetClass);

	InfoRef->Message = Message;
	InfoRef->AddToViewport(0);

	bIsMessageOnScreen = true;
	CurrentWidgetOnScreen = InfoRef;

	GetWorld()->GetTimerManager().SetTimer(InfoMessageTimerHandle, this, &AWorldKeeper::ClearMessageOnScreen, 3.0f, false);
}

void AWorldKeeper::AddEndMessageOnScreen()
{
	if (!EndGameMessageClass)
	{
		return;
	}

	if (CheckMessageOnScreen())
	{
		ClearMessageOnScreen();
	}

	UEndGameMessageWidget* EndWidget = CreateWidget<UEndGameMessageWidget>(GetWorld(), EndGameMessageClass);

	EndWidget->AddToViewport(0);

	GetWorld()->GetTimerManager().SetTimer(EndMessageTimerHandle, this, &AWorldKeeper::BackToMenu, 3.0f, false);
}

void AWorldKeeper::ClearMessageOnScreen()
{
	if (CurrentWidgetOnScreen)
	{
		CurrentWidgetOnScreen->RemoveFromParent();
	}
}

bool AWorldKeeper::CheckMessageOnScreen()
{
	if (CurrentWidgetOnScreen) return true;
	else return false;
}

void AWorldKeeper::BackToMenu()
{
	UGameplayStatics::OpenLevel(this, "MenuLevel");
}