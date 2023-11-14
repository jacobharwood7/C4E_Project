// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CastSpell.h"

#include "C4EAICharacter.h"
#include "C4EAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CastSpell::UBTTask_CastSpell()
{
	NodeName = TEXT("Cast Spell");
}

EBTNodeResult::Type UBTTask_CastSpell::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	bool OutofRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if(OutofRange)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	AAIController* cont = OwnerComp.GetAIOwner();
	AC4EAICharacter* npc = Cast<AC4EAICharacter>(cont->GetPawn());

	if(IInterface_Input* icombat = Cast<IInterface_Input>(npc))
	{
		npc->Execute_Shoot(npc);
	}

	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}
