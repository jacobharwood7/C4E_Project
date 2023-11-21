// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviourTree/BTTask_FindPlayerLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInit)
{
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0))
	{
		FVector const playerLocation = Player->GetActorLocation();
		if(_searchRandom)
		{
			FNavLocation Loc;
			if (UNavigationSystemV1* const Navsys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				if (Navsys->GetRandomPointInNavigableRadius(playerLocation, _searchRadius, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),Loc.Location);
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerLocation);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;

		}
	}
	return EBTNodeResult::Failed;
}
