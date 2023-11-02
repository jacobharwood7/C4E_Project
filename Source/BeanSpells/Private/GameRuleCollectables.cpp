#include "GameRuleCollectables.h"

#include "Collectable.h"
#include "Kismet/GameplayStatics.h"

UGameRuleCollectables::UGameRuleCollectables()
{
	_amountRemaining = 0;
}

void UGameRuleCollectables::Init()
{
	if(_allCollectables.Num() ==0)
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACollectable::StaticClass(),OutActors);
		for(AActor* a : OutActors)
		{
			_allCollectables.Add(Cast<ACollectable>(a));
		}
	}

	_amountRemaining = _allCollectables.Num();
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Black, FString::Printf(TEXT("Game Rule Collectables found : %d Collectables in world"),_amountRemaining));
	
	
	for(ACollectable* col :_allCollectables)
	{
		col->OnCollected.AddUniqueDynamic(this, &UGameRuleCollectables::Handle_Collected);
	}
	
	Super::Init();
}

void UGameRuleCollectables::Handle_Collected(ACollectable* subject, AController* causer)
{
	_amountRemaining--;
	BroadcastGameRulePointsScored(causer,subject->_pointsValue);

	if(_amountRemaining==0)
	{
		BroadcastGameRuleCompleted();
	}
}
