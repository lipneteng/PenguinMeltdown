// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WorldKeeper.generated.h"

UCLASS()
class PENGUIN_MELTDOWN_API AWorldKeeper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldKeeper();
	
	UPROPERTY(BlueprintReadOnly)
		int32 Score = 0;

	UPROPERTY(EditAnywhere)
		TMap <FName, int32> ScoreMap;

	UPROPERTY(EditAnywhere)
		float TimeDilationMod = 0.1f;

	UPROPERTY(EditAnywhere)
		float ScoreMod = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float GameTimeSeconds = 120.0f;

	UPROPERTY(BlueprintReadWrite)
		bool bIsUnderPause = false;

	UPROPERTY(BlueprintReadWrite)
		float TimeUnderPause = 0.0f;

	UPROPERTY(BlueprintReadWrite)
		bool bIsUnderMultiScore = false;

	UPROPERTY(BlueprintReadWrite)
		float TimeUnderMultiScore = 0.0f;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UInfoWidget> InfoWidgetClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UEndGameMessageWidget> EndGameMessageClass;

	UPROPERTY(EditAnywhere)
		USoundBase* BackgroundMusic;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Pickup mod func
	void AddScorePoints(EPenguinType PenguinsType);

	void SetPauseTime(float TimeUnderPause);

	void SetMultiScoreTime(float TimeUnderMultiScore);

	void AddGameTime(float ValueSeconds);

	void AddInfoMessageOnScreen(FString Message);

	void AddEndMessageOnScreen();

	void ClearMessageOnScreen();

	bool CheckMessageOnScreen();

	void PlayBackgroundMusic();

	//Delegate for pause(time dilation)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimeIsPaused, float, TimeDilValue);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimeIsNotPausedNow);

	UPROPERTY(BlueprintAssignable)
		FTimeIsPaused OnTimeIsPaused;

	UPROPERTY(BlueprintAssignable)
		FTimeIsNotPausedNow OnTimeIsNotPausedNow;

private:
	bool bIsGameEnded = false;

	float DefaultScoreMod = 1.0f;
	float CurrentScoreMod = 1.0f;

	FTimerHandle InfoMessageTimerHandle;
	FTimerHandle EndMessageTimerHandle;

	bool bIsMessageOnScreen = false;
	class UUserWidget* CurrentWidgetOnScreen;

	void CalculateTime(float DeltaSeconds);

	void BackToMenu();
};
