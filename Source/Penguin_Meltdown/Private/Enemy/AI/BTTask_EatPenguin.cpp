// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Seal.h"
#include "SealAIController.h"
#include "Penguin.h"
#include "PlayerPawn_Polar.h"
#include "FunctionsLibrary.h"
#include "BTTask_EatPenguin.h"


UBTTask_EatPenguin::UBTTask_EatPenguin()
{
	NodeName = "Try to eat penguin";
}

EBTNodeResult::Type UBTTask_EatPenguin::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASealAIController* SealAIRef = Cast<ASealAIController>(OwnerComp.GetAIOwner());

	if (SealAIRef)
	{
		ASeal* SealRef = Cast<ASeal>(SealAIRef->GetPawn());
		UObject* PenguinKey = OwnerComp.GetBlackboardComponent()->GetValueAsObject("Penguin");
		APenguin* PenguinRef = Cast<APenguin>(PenguinKey);

		APlayerPawn_Polar* PolarRef = nullptr;
		UFunctionsLibrary::GetPlayerPawn_Polar(this, PolarRef);

		if (!SealRef || !PenguinRef || !PolarRef)
		{
			return EBTNodeResult::Failed;
		}

		float Distance = (PenguinRef->GetActorLocation() - SealRef->GetActorLocation()).Size();

		if (Distance <= DistanceToEat)
		{
			if (PenguinRef->IsPolarControlled())
			{
				PolarRef->ClearPenguinSpecific(PenguinRef);
			}
			else
			{
				PenguinRef->Destroy();
			}
			//Play sound here
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}



