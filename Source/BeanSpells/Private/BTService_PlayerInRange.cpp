// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerInRange.h"

#include "C4EAICharacter.h"
#include "C4EAIController.h"
#include "C4ECharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


UBTService_PlayerInRange::UBTService_PlayerInRange()
{
	bNotifyBecomeRelevant =true;
	NodeName = TEXT("Is Player in Spell Range");
}

void UBTService_PlayerInRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AC4EAIController* cont = Cast<AC4EAIController>(OwnerComp.GetAIOwner());
	AC4EAICharacter* npc = Cast<AC4EAICharacter>(cont->GetPawn());

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),npc->GetDistanceTo(player)<=_spellRange);
	UE_LOG(LogTemp, Display, TEXT("In range is set to %hhd"), (npc->GetDistanceTo(player)<=_spellRange))
}
