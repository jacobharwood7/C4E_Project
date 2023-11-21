#include"Components/Target.h"

#include "Components/Health.h"

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
	for (AActor* ActorFound :FoundActors)
	{
		ActorFound->Destroy();
	}
	GetOwner()->Destroy();
}
