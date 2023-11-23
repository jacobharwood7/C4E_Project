#include "Game/GameRuleTarget.h"

#include "Components/Target.h"
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
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,FString::Printf(TEXT("Targets Found : %d"), _amountRemaining));
	for(UTarget* t : _targets)
	{
		t->OnTargetDestroyed.AddUniqueDynamic(this,&UGameRuleTarget::Handle_TargetDestroyed);
	}
	
	Super::Init();
}

void UGameRuleTarget::Handle_TargetDestroyed(AActor* target, AController* causer)
{
	_amountRemaining--;
	BroadcastGameRulePointsScored(causer,1,0);
	if(_amountRemaining==0)
	{
		BroadcastGameRuleCompleted();
	}
}

void UGameRuleTarget::Handle_TargetSpawned(UTarget* spawned)
{
	_amountRemaining = _targets.Num();
	_targets.Add(spawned);
	spawned->OnTargetDestroyed.AddUniqueDynamic(this,&UGameRuleTarget::Handle_TargetDestroyed);
}

