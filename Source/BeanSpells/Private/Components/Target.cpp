#include"Components/Target.h"
#include "Components/Collectable.h"
#include "Components/Health.h"
#include "Game/GameRuleCollectables.h"

UTarget::UTarget()
{
	
}

void UTarget::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();
	_healthComp = owner->FindComponentByClass<UHealth>();

	if(_healthComp == nullptr)
	{
		_healthComp = NewObject<UHealth>(owner, TEXT("Health"));
		owner->AddInstanceComponent(_healthComp);
		_healthComp->RegisterComponent();
		owner->Modify();
	}

	owner->Tags.Add(FName("gameruletarget"));
	
	_healthComp->OnDead.AddUniqueDynamic(this,&UTarget::Handle_Dead);
}

void UTarget::Handle_Dead(AController* causer)
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Magenta,FString::Printf(TEXT("TARget DIED : ")));
	OnTargetDestroyed.Broadcast(GetOwner(),causer);
	TArray<AActor*> FoundActors = GetOwner()->Children;

	SpawnCoins();
	
	for (AActor* ActorFound :FoundActors)
	{
		ActorFound->Destroy();
	}
	GetOwner()->Destroy();
}

void UTarget::SpawnCoins()
{
	int CoinCount = FMath::RandRange(5,15);
	FVector spawnLocation = GetOwner()->GetActorLocation();
	FRotator spawnRotation = GetOwner()->GetActorRotation();
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	for (int i=0;i<CoinCount;i++)
	{
		if(ACollectable* Coin = GetWorld()->SpawnActor<ACollectable>(_coin,spawnLocation,spawnRotation,spawnParams))
		{
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,FString::Printf(TEXT("COINNNNNNNNNNN")));
			//ASSIGN FUNCTION TO EVENT SOMEHOW
			
			//UGameRuleCollectables::Handle_Spawn(Coin);
		}
	}
}
