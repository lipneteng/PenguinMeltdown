// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToPenguin.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_MELTDOWN_API UBTTask_MoveToPenguin : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_MoveToPenguin();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
