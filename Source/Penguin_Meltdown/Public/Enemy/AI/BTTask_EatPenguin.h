// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_EatPenguin.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_MELTDOWN_API UBTTask_EatPenguin : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DistanceToEat = 200.0f;

		UBTTask_EatPenguin();

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
