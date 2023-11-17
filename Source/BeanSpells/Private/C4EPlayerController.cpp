#include "C4EPlayerController.h"

#include "C4ECharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAsset.h"
#include "WidgetScore.h"
#include "WidgetPause.h"
#include "GameFramework/GameModeBase.h"
#include "Interface_Input.h"
#include "Kismet/GameplayStatics.h"


AC4EPlayerController::AC4EPlayerController() : Super()
{
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

	if(_scoreWidgetClass)
	{
		_scoreWidget = CreateWidget<UWidgetScore,AC4EPlayerController*>(this,_scoreWidgetClass);
		_scoreWidget->AddToViewport();
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
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	_tempPawn = World->SpawnActor<APawn>(_pawnToSpawn,spawnLocation,spawnRotation,spawnParams);
	Possess(_tempPawn);
	if(AC4ECharacter* castedPawn = Cast<AC4ECharacter>(_tempPawn))
	{
		//TODO: Bind to any relevant events
		castedPawn->Init();
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
	if(_pauseWidgetClass)
	{
		_pauseWidget = CreateWidget<UWidgetPause,AC4EPlayerController*>(this,_pauseWidgetClass);
		_pauseWidget->AddToViewport();
		SetShowMouseCursor(true);
		SetInputMode(FInputModeUIOnly());
		UGameplayStatics::SetGamePaused(GetWorld(),true);
	}
	
}
