﻿#include "Player/C4EPlayerController.h"

#include "Player/C4ECharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Health.h"
#include "Components/Inventory.h"
#include "Game/C4EGameMode.h"
#include "Player/InputAsset.h"
#include "Widget/WidgetScore.h"
#include "Widget/WidgetPause.h"
#include "Widget/WidgetCoins.h"
#include "Widget/WidgetWheel.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/Interface_Input.h"
#include "Kismet/GameplayStatics.h"


AC4EPlayerController::AC4EPlayerController() : Super()
{
	
	_playerInv = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	
	_score=0;
}

void AC4EPlayerController::Init_Implementation()
{
	
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(_mappingContext)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(_mappingContext, 0);
		}
	}

	if(GetPawn()!=nullptr)
	{
		GetPawn()->Destroy();
	}

}

void AC4EPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* UEIP= CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if(_inputActions.LoadSynchronous())
		{
			UEIP->BindAction(_inputActions->JumpAction.LoadSynchronous(),ETriggerEvent::Triggered,this,&AC4EPlayerController::Jump);
			UEIP->BindAction(_inputActions->JumpAction.LoadSynchronous(),ETriggerEvent::Completed,this,&AC4EPlayerController::StopJump);
			UEIP->BindAction(_inputActions->MoveAction.LoadSynchronous(),ETriggerEvent::Triggered,this,&AC4EPlayerController::Move);
			UEIP->BindAction(_inputActions->LookAction.LoadSynchronous(),ETriggerEvent::Triggered,this,&AC4EPlayerController::Look);
			UEIP->BindAction(_inputActions->ShootAction.LoadSynchronous(),ETriggerEvent::Triggered,this,&AC4EPlayerController::Shoot);
			
			UEIP->BindAction(_inputActions->PauseAction.LoadSynchronous(),ETriggerEvent::Triggered,this,&AC4EPlayerController::Handle_Paused);
			UEIP->BindAction(_inputActions->SwitchActionOn.LoadSynchronous(),ETriggerEvent::Completed,this,&AC4EPlayerController::Handle_SwitchWeapon);
			//not firing in ui mode
			//UEIP->BindAction(_inputActions->SwitchActionOff.LoadSynchronous(),ETriggerEvent::Triggered,this,&AC4EPlayerController::Handle_FinishSwitchWeapon);

			UEIP->BindAction(_inputActions->ViewAction.LoadSynchronous(),ETriggerEvent::Triggered,this,&AC4EPlayerController::ChangeView);

		}
	}
}

void AC4EPlayerController::Handle_MatchStarted_Implementation()
{
	UWorld* const World = GetWorld();
	AActor* TempStart = UGameplayStatics::GetGameMode(World)->FindPlayerStart(this);
	FVector spawnLocation = TempStart!=nullptr ? TempStart->GetActorLocation():FVector::ZeroVector;
	FRotator spawnRotation = TempStart!=nullptr ? TempStart->GetActorRotation():FRotator::ZeroRotator;
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	_tempPawn = World->SpawnActor<APawn>(_pawnToSpawn,spawnLocation,spawnRotation,spawnParams);
	Possess(_tempPawn);
	if(AC4ECharacter* castedPawn = Cast<AC4ECharacter>(_tempPawn))
	{
		//TODO: Bind to any relevant events
		castedPawn->Init();
		castedPawn->_health->OnDead.AddUniqueDynamic(this,&AC4EPlayerController::Handle_Dead);
		castedPawn->_health->OnDamaged.AddUniqueDynamic(this,&AC4EPlayerController::Handle_Damage);
		_maxHealth = castedPawn->_health->_maxHealth;
	}

	if(_scoreWidgetClass)
	{
		_scoreWidget = CreateWidget<UWidgetScore,AC4EPlayerController*>(this,_scoreWidgetClass);
		_scoreWidget->AddToViewport();
	}
	if(_coinWidgetClass)
	{
		_coinWidget = CreateWidget<UWidgetCoins,AC4EPlayerController*>(this,_coinWidgetClass);
		_coinWidget->AddToViewport();
	}

}

void AC4EPlayerController::Handle_MatchEnded_Implementation()
{
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}

void AC4EPlayerController::AddScore(int amount)
{
	_score +=amount;
	if(_scoreWidget != nullptr)
	{
		_scoreWidget->UpdateScore(_score);
	}
}

void AC4EPlayerController::AddCoin(int amount)
{
	_coins +=amount;
	if(_coinWidget!= nullptr)
	{
		_coinWidget->UpdateCoins(_coins);
	}
}

void AC4EPlayerController::Move(const FInputActionValue& Input)
{
	IInterface_Input::Execute_Move(_tempPawn, Input);
}

void AC4EPlayerController::Look(const FInputActionValue& Input)
{	
	IInterface_Input::Execute_Look(_tempPawn, Input);
}

void AC4EPlayerController::Shoot()
{
	IInterface_Input::Execute_Shoot(_tempPawn);
}

void AC4EPlayerController::Jump()
{
	IInterface_Input::Execute_Jump(_tempPawn);
}

void AC4EPlayerController::StopJump()
{
	IInterface_Input::Execute_StopJump(_tempPawn);
}

void AC4EPlayerController::Handle_Paused()
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("Pause ATTEMPT"));
	if(_pauseWidgetClass)
	{
		_pauseWidget = CreateWidget<UWidgetPause,AC4EPlayerController*>(this,_pauseWidgetClass);
		_pauseWidget->AddToViewport();
		SetShowMouseCursor(true);
		SetInputMode(FInputModeUIOnly());
		UGameplayStatics::SetGamePaused(GetWorld(),true);
	}
}


void AC4EPlayerController::Handle_Dead(AController* causer)
{
	
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Orange,TEXT("I AM Dead"));
	_scoreWidget->RemoveFromParent();
	_scoreWidget->Destruct();
	_coinWidget->RemoveFromParent();
	_coinWidget->Destruct();
	Cast<AC4EGameMode>(GetWorld()->GetAuthGameMode())->EndMatch();
}

void AC4EPlayerController::Handle_Damage(float newhealth)
{
	_scoreWidget->UpdateHealth(newhealth/_maxHealth, _maxHealth);
}

void AC4EPlayerController::Handle_SwitchWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("SWITCH ATTEMPT"));
	if(_wheelWidgetClass)
	{
		_wheelWidget = CreateWidget<UWidgetWheel,AC4EPlayerController*>(this,_wheelWidgetClass);
		_wheelWidget->AddToViewport();
		SetShowMouseCursor(true);
		SetInputMode(FInputModeUIOnly());
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(),0.2);
		
	}
}

void AC4EPlayerController::Handle_FinishSwitchWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("Finished ATTEMPT"));
	if (_wheelWidget)
	{
		if(_wheelWidgetClass)
		{
			_wheelWidget->RemoveFromParent();
			SetShowMouseCursor(false);
			SetInputMode(FInputModeGameOnly());
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(),1.0f);
		}		
	}	
}

void AC4EPlayerController::ChangeView()
{
	AC4ECharacter* castedPawn = Cast<AC4ECharacter>(_tempPawn);
	castedPawn->ChangeView();
}
