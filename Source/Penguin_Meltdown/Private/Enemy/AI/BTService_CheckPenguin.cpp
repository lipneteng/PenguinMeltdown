// Fill out your copyright notice in the Description page of Project Settings.

#include "Penguin_Meltdown.h"
#include "FunctionsLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Seal.h"
#include "SealAIController.h"
#include "BTService_CheckPenguin.h"

void UBTService_CheckPenguin::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ASealAIController* SealAIRef = Cast<ASealAIController>(OwnerComp.GetAIOwner());
	Seal = Cast<ASeal>(SealAIRef->GetPawn());

	APenguin* PenguinRef = nullptr;

	if (SealAIRef && Seal)
	{
		if (Seal->IsDead())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsEnum("SealBehaviorType", static_cast<uint8>(ESealBehaviorType::Dead));
			return;
		}

		if (CheckDistanceToPolar())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject("Penguin", TargetNewPenguin());
			OwnerComp.GetBlackboardComponent()->SetValueAsEnum("SealBehaviorType", static_cast<uint8>(ESealBehaviorType::FindPenguin));

			UObject* PenguinKey = OwnerComp.GetBlackboardComponent()->GetValueAsObject("Penguin");
			if (!PenguinKey)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum("SealBehaviorType", static_cast<uint8>(ESealBehaviorType::Idle));
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsEnum("SealBehaviorType", static_cast<uint8>(ESealBehaviorType::FindPlayer));
		}
	}
}

bool UBTService_CheckPenguin::CheckDistanceToPolar()
{
	APlayerPawn_Polar* PolarRef = nullptr;
	UFunctionsLibrary::GetPlayerPawn_Polar(this, PolarRef);

	if (PolarRef && Seal)
	{
		float Distance = (PolarRef->GetActorLocation() - Seal->GetActorLocation()).Size();

		if (Distance <= DistancePlayerFollowing)
		{
			return true;
		}
	}

	return false;
}

APenguin* UBTService_CheckPenguin::TargetNewPenguin()
{
	APenguin* TargetPenguin = nullptr;
	TArray <APenguin*> Penguins;

	UFunctionsLibrary::GetCurrentPenguinsOnMap(this, Penguins);

	for (int32 i = 0; i < Penguins.Num(); i++)
	{
		float MinDistance = 0.0f;
		float Distance = 0.0f;

		APenguin* PenguinRef = Penguins[i];

		if (PenguinRef)
		{
			Distance = (PenguinRef->GetActorLocation() - Seal->GetActorLocation()).Size();

			if (Distance <= MinDistance || i == 0)
			{
				TargetPenguin = PenguinRef;
				MinDistance = Distance;
			}
		}
	}

	return TargetPenguin;
}