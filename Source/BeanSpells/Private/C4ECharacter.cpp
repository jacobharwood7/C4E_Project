#include "C4ECharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Fireable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Weapon_Base.h"
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

	SetupStimulusSource();
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

void AC4ECharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
 {
	if(UEnhancedInputComponent* UEIP= CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		UEIP->BindAction(JumpAction,ETriggerEvent::Triggered,this,&ACharacter::Jump);
		UEIP->BindAction(JumpAction,ETriggerEvent::Completed,this,&ACharacter::StopJumping);
		
		UEIP->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AC4ECharacter::Move);
		
		UEIP->BindAction(LookAction,ETriggerEvent::Triggered,this,&AC4ECharacter::Look);
		
		UEIP->BindAction(ShootAction,ETriggerEvent::Triggered,this,&AC4ECharacter::Shoot);
		
		UEIP->BindAction(PauseAction,ETriggerEvent::Triggered,this,&AC4ECharacter::Pause);
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

void AC4ECharacter::Move(const FInputActionValue& value)
{
	FVector2d movementVector = value.Get<FVector2D>();
	if (Controller!=nullptr)
	{
		AddMovementInput(GetActorForwardVector(),movementVector.Y);
		AddMovementInput(GetActorRightVector(),movementVector.X);

	}
}

void AC4ECharacter::Look(const FInputActionValue& value)
{
	FVector2d LookAxisVector = value.Get<FVector2d>();
	if (Controller!=nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AC4ECharacter::Shoot()
{
	if (_FireableRef)
	{
		IFireable::Execute_Fire(_FireableRef);
	}
}

void AC4ECharacter::Pause()
{
	OnPause.Broadcast();
}
