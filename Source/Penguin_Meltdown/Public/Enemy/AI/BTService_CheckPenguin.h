// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "Penguin.h"
#include "BTService_CheckPenguin.generated.h"

UENUM(BlueprintType)
enum class ESealBehaviorType : uint8
{
	Idle 		UMETA(DisplayName = "Idle"),
	FindPlayer 	UMETA(DisplayName = "FindPlayer"),
	FindPenguin	UMETA(DisplayName = "FindPenguin"),
	Dead		UMETA(DisplayName = "Dead")
};	

UCLASS()
class PENGUIN_MELTDOWN_API UBTService_CheckPenguin : public UBTService
{
	GENERATED_BODY()

public:

	class ASeal* Seal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DistancePlayerFollowing = 2000.0f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool CheckDistanceToPolar();

	APenguin* TargetNewPenguin();
};
