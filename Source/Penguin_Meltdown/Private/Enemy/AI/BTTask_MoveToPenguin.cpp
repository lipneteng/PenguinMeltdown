// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "SealAIController.h"
#include "Penguin.h"
#include "BTTask_MoveToPenguin.h"


UBTTask_MoveToPenguin::UBTTask_MoveToPenguin()
{
	NodeName = "Move To Penguin";
}

EBTNodeResult::Type UBTTask_MoveToPenguin::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASealAIController* SealAIRef = Cast<ASealAIController>(OwnerComp.GetAIOwner());

	if (SealAIRef)
	{
		UObject* PenguinKey = OwnerComp.GetBlackboardComponent()->GetValueAsObject("Penguin");
		APenguin* PenguinRef = Cast<APenguin>(PenguinKey);

		if (PenguinRef)
		{
			SealAIRef->MoveToActor(PenguinRef);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
