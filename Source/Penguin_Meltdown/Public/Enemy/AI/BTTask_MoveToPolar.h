// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToPolar.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_MELTDOWN_API UBTTask_MoveToPolar : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_MoveToPolar();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
