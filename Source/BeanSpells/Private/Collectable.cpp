#include "Collectable.h"

#include "C4ECharacter.h"
#include "C4EPlayerController.h"
#include "Components/SphereComponent.h"

ACollectable::ACollectable()
{
	_pointsValue = 1;
	_collision =CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = _collision;
}


void ACollectable::BroadcastCollected(AController* causer)
{
	OnCollected.Broadcast(this,causer);
	Destroy();
}
