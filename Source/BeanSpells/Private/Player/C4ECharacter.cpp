#include "Player/C4ECharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "Components/Health.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/Fireable.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapons/Weapon_Base.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

AC4ECharacter::AC4ECharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.0f,96.0f);
	_cameraBoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Boom Arm"));
	_cameraBoomArm->SetupAttachment(RootComponent);
	_cameraBoomArm->TargetArmLength = 350.0f;
	_cameraBoomArm->bUsePawnControlRotation = true;
	
	_TPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	_TPCamera->SetupAttachment(_cameraBoomArm);
	_TPCamera->bUsePawnControlRotation = true;
	_TPCamera->bAutoActivate = true;
	_CurrentCamera = _TPCamera;
	
	_FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	_FPCamera->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("head"));
	_FPCamera->bUsePawnControlRotation = true;
	_FPCamera->bAutoActivate = false;

	_weaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	
	_weaponAttachPoint->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("hand_r"));

	
	_footCoinCollection = CreateDefaultSubobject<UBoxComponent>(TEXT("Feet"));
	_footCoinCollection->SetupAttachment(GetCapsuleComponent());

	_health = CreateDefaultSubobject<UHealth>(TEXT("Health"));
	
	SetupStimulusSource();

	
}

void AC4ECharacter::Move_Implementation(const FInputActionValue& Input)
{
	if(Controller)
	{
		FVector2d movementVector = Input.Get<FVector2D>();
		
		
		AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.0,GetControlRotation().Yaw,0.0)),movementVector.Y);
		AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.0,GetControlRotation().Yaw,GetControlRotation().Roll)),movementVector.X);
	}
}

void AC4ECharacter::Look_Implementation(const FInputActionValue& Input)
{
	if(Controller)
	{
		FVector2d LookAxisVector = Input.Get<FVector2d>();

		AddControllerYawInput(LookAxisVector.X*0.5);
		AddControllerPitchInput(LookAxisVector.Y*0.5);

		_weaponAttachPoint->SetRelativeRotation(_CurrentCamera->GetRelativeRotation());
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
	bUseControllerRotationYaw = false;
	
	if(_defaultWeapon)
	{
		ChangeWeapon(_defaultWeapon);
	}
}


void AC4ECharacter::ChangeView()
{	
	if(_TPCamera->IsActive())
	{
		_FPCamera->SetActive(true);
		_TPCamera->SetActive(false);
		_CurrentCamera = _FPCamera;
		bUseControllerRotationYaw =true;
	}
	else
	{
		_TPCamera->SetActive(true);
		_FPCamera->SetActive(false);
		_CurrentCamera = _TPCamera;
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

void AC4ECharacter::ChangeWeapon(TSubclassOf<AWeapon_Base> newWeapon)
{
	TArray<AActor*> FoundActors = this->Children;
	for (AActor* ActorFound :FoundActors)
	{
		ActorFound->Destroy();
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("DEAD CHILDREN HAHA"));
	}
	
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = this;
	TObjectPtr<AWeapon_Base> spawnedGun = GetWorld()->SpawnActor<AWeapon_Base>(newWeapon.Get(), _weaponAttachPoint->GetComponentTransform(),spawnParams);
	spawnedGun->AttachToComponent(_weaponAttachPoint,FAttachmentTransformRules::SnapToTargetIncludingScale);
	if(UKismetSystemLibrary::DoesImplementInterface(spawnedGun, UFireable::StaticClass()))
	{
		_FireableRef = spawnedGun;
	}

	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Emerald,TEXT("Weapon Equip Attempt"));
}
