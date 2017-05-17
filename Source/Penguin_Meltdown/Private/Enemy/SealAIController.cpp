// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "SealAIController.h"

ASealAIController::ASealAIController()
{
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
}

void ASealAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	if (BehaviorTreeAsset)
	{
		BlackBoardComp->InitializeBlackboard(*BehaviorTreeAsset->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTreeAsset);
	}
}