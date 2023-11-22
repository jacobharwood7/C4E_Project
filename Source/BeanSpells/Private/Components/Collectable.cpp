#include "Components/Collectable.h"

#include "Player/C4ECharacter.h"
#include "Player/C4EPlayerController.h"
#include "Components/SphereComponent.h"

ACollectable::ACollectable()
{
	_pointsValue = 1;
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;
	_mesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Mesh"));
}


void ACollectable::BroadcastCollected(AController* causer)
{
	OnCollected.Broadcast(this,causer);
	Destroy();
}
