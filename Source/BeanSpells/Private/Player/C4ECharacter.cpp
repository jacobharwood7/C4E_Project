#include "Player/C4ECharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "Components/Inventory.h"
#include "Interfaces/Fireable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapons/Weapon_Base.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

AC4ECharacter::AC4ECharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.0f,96.0f);
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_camera->SetupAttachment(GetCapsuleComponent());
	_camera->SetRelativeLocation(FVector(-10.0f,0.0f,60.0f));
	_camera->bUsePawnControlRotation = true;

	_weaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	_weaponAttachPoint->SetupAttachment(_camera);

	
	_footCoinCollection = CreateDefaultSubobject<UBoxComponent>(TEXT("Feet"));
	_footCoinCollection->SetupAttachment(GetCapsuleComponent());
	
	
	SetupStimulusSource();
}

void AC4ECharacter::Move_Implementation(const FInputActionValue& Input)
{
	if(Controller)
	{
		FVector2d movementVector = Input.Get<FVector2D>();
		
		AddMovementInput(GetActorForwardVector(),movementVector.Y);
		AddMovementInput(GetActorRightVector(),movementVector.X);
		
	}
}

void AC4ECharacter::Look_Implementation(const FInputActionValue& Input)
{
	if(Controller)
	{
		FVector2d LookAxisVector = Input.Get<FVector2d>();
	
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AC4ECharacter::Shoot_Implementation()
{
	if(Controller)
	{
		if (_FireableRef)
		{
			IFireable::Execute_Fire(_FireableRef);
		}
	}
}

void AC4ECharacter::Jump_Implementation()
{
	if(Controller)
	{
		Super::Jump();
	}
}

void AC4ECharacter::StopJump_Implementation()
{
	if(Controller)
	{
		Super::StopJumping();
	}
}

void AC4ECharacter::Init_Implementation()
{
	if(_CurrentWeapon)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;
		TObjectPtr<AWeapon_Base> spawnedGun = GetWorld()->SpawnActor<AWeapon_Base>(_CurrentWeapon.Get(), _weaponAttachPoint->GetComponentTransform(),spawnParams);
		spawnedGun->AttachToComponent(_weaponAttachPoint,FAttachmentTransformRules::SnapToTargetIncludingScale);
		if(UKismetSystemLibrary::DoesImplementInterface(spawnedGun, UFireable::StaticClass()))
		{
			_FireableRef = spawnedGun;
		}
	}
}


void AC4ECharacter::SetupStimulusSource()
{
	stimSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if(stimSource)
	{
		stimSource->RegisterForSense(TSubclassOf<UAISense_Sight>());//register this stimulus for the sight system
		stimSource->RegisterWithPerceptionSystem();//register this stimulus with the perception system
	}
}
