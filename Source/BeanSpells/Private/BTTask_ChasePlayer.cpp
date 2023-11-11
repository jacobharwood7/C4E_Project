// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
	NodeName = TEXT("Chase player");
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{  
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
