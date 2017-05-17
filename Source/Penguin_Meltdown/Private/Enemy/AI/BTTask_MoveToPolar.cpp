// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "SealAIController.h"
#include "PlayerPawn_Polar.h"
#include "FunctionsLibrary.h"
#include "BTTask_MoveToPolar.h"

UBTTask_MoveToPolar::UBTTask_MoveToPolar()
{
	NodeName = "Move to polar";
}

EBTNodeResult::Type UBTTask_MoveToPolar::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASealAIController* SealAIRef = Cast<ASealAIController>(OwnerComp.GetAIOwner());

	if (SealAIRef)
	{
		APlayerPawn_Polar* PolarRef = nullptr;
		UFunctionsLibrary::GetPlayerPawn_Polar(this, PolarRef);

		if (PolarRef)
		{
			SealAIRef->MoveToActor(PolarRef);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

