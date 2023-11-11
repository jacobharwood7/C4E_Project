#include "C4EAICharacter.h"

#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Fireable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Weapon_Base.h"


// Sets default values
AC4EAICharacter::AC4EAICharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.0f,96.0f);
	_weaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	_weaponAttachPoint->SetupAttachment(GetCapsuleComponent());
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

void AC4EAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if(UEnhancedInputComponent* UEIP= CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{		
		UEIP->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AC4EAICharacter::Move);
		
		UEIP->BindAction(LookAction,ETriggerEvent::Triggered,this,&AC4EAICharacter::Look);
		
		UEIP->BindAction(ShootAction,ETriggerEvent::Triggered,this,&AC4EAICharacter::Shoot);
	}}


void AC4EAICharacter::Move(const FInputActionValue& value)
{
	FVector2d movementVector = value.Get<FVector2D>();
	if (Controller!=nullptr)
	{
		AddMovementInput(GetActorForwardVector(),movementVector.Y);
		AddMovementInput(GetActorRightVector(),movementVector.X);
	}
}

void AC4EAICharacter::Look(const FInputActionValue& value)
{
	FVector2d LookAxisVector = value.Get<FVector2d>();
	if (Controller!=nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AC4EAICharacter::Shoot()
{
	if (_FireableRef)
	{
		IFireable::Execute_Fire(_FireableRef);
	}
}

