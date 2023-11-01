#include "ProjectileWeapon.h"

#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogProj, Display, All);


bool AProjectileWeapon::Fire_Implementation()
{
	UE_LOG(LogProj,Display, TEXT("FIRING PROJECTILE CLASS"))

	UWorld* const world=GetWorld();

	if(world == nullptr||_projectile == nullptr){return false;}

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	world->SpawnActor(_projectile, &_Muzzle->GetComponentTransform(), spawnParams);

	return true;
}
