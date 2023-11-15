#include "C4EAICharacter.h"

#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Fireable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Target.h"
#include "Weapon_Base.h"


// Sets default values
AC4EAICharacter::AC4EAICharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.0f,96.0f);
	_weaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	_weaponAttachPoint->SetupAttachment(GetCapsuleComponent());
	_target = CreateDefaultSubobject<UTarget>(TEXT("Target"));
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


void AC4EAICharacter::Move_Implementation(const FInputActionValue& value)
{
	FVector2d movementVector = value.Get<FVector2D>();
	if (Controller!=nullptr)
	{
		AddMovementInput(GetActorForwardVector(),movementVector.Y);
		AddMovementInput(GetActorRightVector(),movementVector.X);
	}
}

void AC4EAICharacter::Look_Implementation(const FInputActionValue& value)
{
	FVector2d LookAxisVector = value.Get<FVector2d>();
	if (Controller!=nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AC4EAICharacter::Shoot_Implementation()
{
	if (_FireableRef)
	{
		IFireable::Execute_Fire(_FireableRef);
	}
}

