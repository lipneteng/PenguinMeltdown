// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Iceland.generated.h"

UENUM(BlueprintType)
enum class EIcelandState : uint8
{
	Free 	UMETA(DisplayName = "Free"),
	Penguin UMETA(DisplayName = "Penguin"),
	Pickup	UMETA(DisplayName = "Pickup")
};

UCLASS()
class PENGUIN_MELTDOWN_API AIceland : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIceland();

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* DefaultScene;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* IcelandMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveToBorder(float Delta);

	void SetSpeed(float SpeedValue);
	float GetSpeed() const;

	void SetDirection(FVector DirectionValue);
	FVector GetDirection() const;

	void SetState(EIcelandState NewState);
	EIcelandState GetState() const;
	
	void SetActorOnIceland(AActor* ActorRef);
	AActor* GetActorOnIceland() const;

	void SetNumberXLine(int32 NumXLine);
	int32 GetNumberXLine() const;

	UFUNCTION()
		void BindOnTimeIsPaused(float TimeDilValue);

	UFUNCTION()
		void BindOnTimeIsNotPausedNow();

private:
	UPROPERTY()
		float Speed = 100.0f;

	UPROPERTY()
		FVector Direction = FVector(0.0f, 1.0f, 0.0f);

	UPROPERTY()
		EIcelandState State = EIcelandState::Free;

	UPROPERTY()
		AActor* ActorOnIceland = nullptr;

	UPROPERTY()
		int32 NumberXLine = 0;
	
};
