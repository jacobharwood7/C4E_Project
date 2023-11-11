// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"

#include "C4EAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
	NodeName = TEXT("Chase player");
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{  
	if(AC4EAIController* cont = Cast<AC4EAIController>(OwnerComp.GetOwner()))
	{
		FVector PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector((GetSelectedBlackboardKey()));

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont,PlayerLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
