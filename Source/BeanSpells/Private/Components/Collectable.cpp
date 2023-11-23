#include "Components/Collectable.h"


ACollectable::ACollectable()
{
	_pointsValue = 1;
	//_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = _mesh;
}


void ACollectable::BroadcastCollected(AController* causer)
{
	OnCollected.Broadcast(this,causer);
	Destroy();
}
