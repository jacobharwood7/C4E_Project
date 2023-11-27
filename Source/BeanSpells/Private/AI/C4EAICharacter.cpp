#include "AI/C4EAICharacter.h"

#include "Components/CapsuleComponent.h"
#include "Interfaces/Fireable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Target.h"
#include "Components/WidgetComponent.h"
#include "Weapons/Weapon_Base.h"
#include "Widget/WidgetDamage.h"


// Sets default values
AC4EAICharacter::AC4EAICharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.0f,96.0f);
	_weaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	_weaponAttachPoint->SetupAttachment(GetCapsuleComponent());
	_target = CreateDefaultSubobject<UTarget>(TEXT("Target"));
	_damageComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamagePoints"));
	this->OnTakeAnyDamage.AddUniqueDynamic(this,&AC4EAICharacter::DamagePoints);
	_damageComp->SetWidgetClass(_damageWidgetClass);
}

UBehaviorTree* AC4EAICharacter::GetBehaviourTree()
{
	return _behaviourTree;
}

void AC4EAICharacter::Init_Implementation()
{
	if(_CurrentWeapon)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;
		TObjectPtr<AWeapon_Base> spawnedGun = GetWorld()->SpawnActor<AWeapon_Base>(_CurrentWeapon.Get(), _weaponAttachPoint->GetComponentTransform(),spawnParams);
		spawnedGun->AttachToComponent(_weaponAttachPoint,FAttachmentTransformRules::SnapToTargetIncludingScale);
		spawnedGun->Init(_DefaultWeaponType);
		if(UKismetSystemLibrary::DoesImplementInterface(spawnedGun, UFireable::StaticClass()))
		{
			_FireableRef = spawnedGun;
		}
	}
}

void AC4EAICharacter::Shoot_Implementation()
{
	if (_FireableRef)
	{
		IFireable::Execute_Fire(_FireableRef);
	}
}

void AC4EAICharacter::DamagePoints(AActor* damagedActor, float damage, const UDamageType* damageType,
						  AController* damageInstigator, AActor* causer)
{
	_damageWidget = Cast<UWidgetDamage>(_damageComp->GetUserWidgetObject());
	_damageWidget->Damage(damage);
}
