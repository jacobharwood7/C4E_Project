#include "BTTask_FindRandomLocation.h"

#include "C4EAICharacter.h"
#include "C4EAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInit)
{
	NodeName = "Find Random Location in Nav Mesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AC4EAIController* const Ai = Cast<AC4EAIController>(OwnerComp.GetAIOwner()))
	{
		if(APawn* NPC = Ai->GetPawn())
		{
			FVector const origin = NPC->GetActorLocation();
			if(UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation loc;
				if(NavSys -> GetRandomPointInNavigableRadius(origin,_searchRadius, loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), loc.Location);
				}
				FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
