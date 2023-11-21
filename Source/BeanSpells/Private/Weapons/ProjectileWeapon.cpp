
#include "Weapons/ProjectileWeapon.h"
#include "Weapons/WeaponType.h"

#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogProj, Display, All);


bool AProjectileWeapon::Fire_Implementation()
{
	_typeData->_damage;

	UWorld* const world=GetWorld();

	if(world == nullptr||_projectile == nullptr){return false;}

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	AProjectile* p = Cast<AProjectile>( world->SpawnActor(_projectile, &_Muzzle->GetComponentTransform(), spawnParams));
	p->_damage = _typeData->_damage;

	return true;
}
