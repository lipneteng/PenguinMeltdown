// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "SealAIController.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_MELTDOWN_API ASealAIController : public AAIController
{
	GENERATED_BODY()

	ASealAIController();

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY()
		class UBlackboardComponent* BlackBoardComp;

	UPROPERTY()
		class UBehaviorTreeComponent* BehaviorTreeComp;
	
	virtual void Possess(APawn* InPawn) override;
};
