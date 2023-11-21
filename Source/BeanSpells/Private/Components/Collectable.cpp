#include "Components/Collectable.h"

#include "Player/C4ECharacter.h"
#include "Player/C4EPlayerController.h"
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
