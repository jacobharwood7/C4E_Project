// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CastSpell.generated.h"

/**
 * 
 */
UCLASS()
class BEANSPELLS_API UBTTask_CastSpell : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_CastSpell();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
