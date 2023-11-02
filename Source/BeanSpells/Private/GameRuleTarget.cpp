#include "GameRuleTarget.h"

#include "Target.h"
#include "Kismet/GameplayStatics.h"

UGameRuleTarget::UGameRuleTarget()
{
	
}

void UGameRuleTarget::Init()
{
	if(_targets.Num()==0)
	{
		TArray<AActor*> outActor;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(),FName("gameruletarget"),outActor);
		for(AActor* a :outActor)
		{
			_targets.Add(Cast<UTarget> (a->GetComponentByClass(UTarget::StaticClass())));
		}
	}
	_amountRemaining = _targets.Num();
	for(UTarget* t : _targets)
	{
		t->OnTargetDestroyed.AddUniqueDynamic(this,&UGameRuleTarget::Handle_TargetDestroyed);
	}
	
	Super::Init();
}

void UGameRuleTarget::Handle_TargetDestroyed(AActor* target, AController* causer)
{
	_amountRemaining--;
	BroadcastGameRulePointsScored(causer,1);
	if(_amountRemaining==0)
	{
		BroadcastGameRuleCompleted();
	}
}
