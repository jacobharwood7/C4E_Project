// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/C4EGameMode.h"

#include "AIHelpers.h"
#include "Game/GameRule.h"
#include "Game/C4EGameState.h"

#include "AI/C4EAICharacter.h"
#include "AI/C4EAIController.h"
#include "Player/C4EPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Widget/WidgetMainMenu.h"
#include "GameFramework/PlayerStart.h"
#include "Interfaces/MatchStateHandler.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/Target.h"
#include "Game/GameRuleTarget.h"
#include "Widget/WidgetDead.h"

AC4EGameMode::AC4EGameMode() : Super()
{
	_countdownTimer = 3;
	_gameRulesLeft = 0;
}

AActor* AC4EGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if(_playerStarts.Num()==0)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerStart::StaticClass(),_playerStarts);
	}
	if(_playerStarts.Num() > 0)
	{
		return _playerStarts[0];
	}
	return nullptr;
}

void AC4EGameMode::PostLogin(APlayerController* NewPlayer)
{
	_playerControllers.AddUnique(NewPlayer);
	if(AC4EPlayerController* castedPC = Cast<AC4EPlayerController>(NewPlayer))
	{
		//TODO bind to relevant event
		castedPC->Init();
	}
	Super::PostLogin(NewPlayer);
}

void AC4EGameMode::Logout(AController* Exiting)
{
	_playerControllers.Remove(Exiting);
	Super::Logout(Exiting);
}

void AC4EGameMode::Handle_GameRuleCompleted(UGameRule* rule)
{
	if(*_gameRuleManagers.Find(rule)){return;}

	_gameRulesLeft--;
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Blue,FString::Printf(TEXT("Game Rule completed. %d Remaining"), _gameRulesLeft));
	if(_gameRulesLeft!=0||_playerControllers.Num()!=0){return;}
	EndMatch();
}

void AC4EGameMode::Handle_GameRulePointsScored(AController* scorer, int points,int type)
{
	
	AC4EPlayerController* castedPC = Cast<AC4EPlayerController>(scorer);
	if(castedPC)
	{
		switch(type)
		{
		case 0:
			castedPC->AddScore(points);
			break;
		case 1:
			castedPC->AddCoin(points);
		default: ;
		}
	}
}

void AC4EGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(_TimerSpawnerHandle,this,&AC4EGameMode::SpawnAI,2.0f,true);
	GetWorld()->GetTimerManager().PauseTimer(_TimerSpawnerHandle);
}


void AC4EGameMode::HandleMatchIsWaitingToStart()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),FName("AISpawn"),_spawnPoints);
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Orange,FString::Printf(TEXT("Number of AI Spawn Points is : %d"),_spawnPoints.Num()));

	TArray<AActor*> pawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACharacter::StaticClass(),pawns);
	
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Blue,FString::Printf(TEXT("pawns : %d"),pawns.Num()));
	
	for (auto p : pawns)
	{
		TArray<AActor*> FoundActors = p->Children;
		for (AActor* ActorFound :FoundActors)
		{
			ActorFound->Destroy();
		}
		p->Destroy();
	}
	SetUpMenu();
	
	Super::HandleMatchIsWaitingToStart();

}

void AC4EGameMode::HandleMatchHasStarted()
{
	if(_menuWidget)
	{
		_menuWidget->RemoveFromParent();		
	}
	GetWorld()->GetTimerManager().UnPauseTimer(_TimerSpawnerHandle);
	TArray<UActorComponent*> outComponents;
	GetComponents(outComponents);
	for(UActorComponent* comp : outComponents)
	{
		if(UGameRule* rule = Cast<UGameRule>(comp))
		{
			_gameRuleManagers.Add(rule, rule->_isOptional);
			rule->Init();
			rule->OnGameRuleCompleted.AddUniqueDynamic(this,&AC4EGameMode::Handle_GameRuleCompleted);
			rule->OnGameRulePointsScored.AddUniqueDynamic(this,&AC4EGameMode::Handle_GameRulePointsScored);

			if(!rule->_isOptional)
			{
				_gameRulesLeft++;
			}
		}
	}
	
	for(AController* controller:_playerControllers)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("1"));
		if(UKismetSystemLibrary::DoesImplementInterface(controller,UMatchStateHandler::StaticClass()))
		{
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("PLAYER has interface"));
			
			IMatchStateHandler::Execute_Handle_MatchStarted(controller);
		}
	}

	/*--SPAWN AI--*/
	
	
	
	Super::HandleMatchHasStarted();
}

void AC4EGameMode::HandleMatchHasEnded()
{
	for(AController*controller:_playerControllers)
    {
        if(UKismetSystemLibrary::DoesImplementInterface(controller,UMatchStateHandler::StaticClass()))
        {
            IMatchStateHandler::Execute_Handle_MatchEnded(controller);
        }
    }
	if(_deathWidgetClass)
	{
	    if(AC4EPlayerController* PC = Cast<AC4EPlayerController>(_playerControllers[0]))
	    {
	        _deathWidget = CreateWidget<UWidgetDead,AC4EPlayerController*>(PC,_deathWidgetClass);
	        _deathWidget->AddToViewport();
			PC->SetShowMouseCursor(true);
			PC->SetInputMode(FInputModeUIOnly());
	        _deathWidget->OnReturn.AddUniqueDynamic(this,&AC4EGameMode::Restart);
	    }
	}
	GetWorld()->GetTimerManager().PauseTimer(_TimerSpawnerHandle);
	Super::HandleMatchHasEnded();
}

void AC4EGameMode::OnMatchStateSet()
{
	FString output;
	if(MatchState==MatchState::WaitingToStart)
	{
		output = "Waiting to start";
	}
	else if(MatchState==MatchState::InProgress)
	{
		output = "In Progress";
	}
	else if(MatchState==MatchState::WaitingPostMatch)
	{
		output = "Waiting post match";
	}
	else if(MatchState==MatchState::LeavingMap)
	{
		output = "Leaving map";
	}

	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Turquoise,FString::Printf(TEXT("State Changed to %s"), *output));
	
	Super::OnMatchStateSet();
}

bool AC4EGameMode::ReadyToStartMatch_Implementation()
{
	return false;
}

bool AC4EGameMode::ReadyToEndMatch_Implementation()
{
	return false;
}


void AC4EGameMode::SpawnAI()
{
	int chosenSpawn = FMath::RandRange(0,_spawnPoints.Num()-1);
	FVector spawnLocation = _spawnPoints[chosenSpawn]->GetActorLocation();
	FRotator spawnRotation = _spawnPoints[chosenSpawn]->GetActorRotation();
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	if(AC4EAICharacter* AI = GetWorld()->SpawnActor<AC4EAICharacter>(AIPawn,spawnLocation,spawnRotation,spawnParams))
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,TEXT("SPAWNING DEATH EATER"));
		
		UGameRuleTarget* TargetRule = FindComponentByClass<UGameRuleTarget>();
		TargetRule->Handle_TargetSpawned(AI->FindComponentByClass<UTarget>());
	}
}

void AC4EGameMode::SetUpMenu()
{
	if(_menuWidgetClass)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Blue,FString::Printf(TEXT("pcs : %d"),_playerControllers.Num()));
		AC4EPlayerController* PC = Cast<AC4EPlayerController>(_playerControllers[0]);
		PC->Init();
		PC->SetInitialLocationAndRotation(menuPoint->GetActorLocation(),menuPoint->GetActorRotation());
		_menuWidget = CreateWidget<UWidgetMainMenu,AC4EPlayerController*>(PC,_menuWidgetClass);
		if(_menuWidget->IsInViewport()){/*do nothing*/}
		else{_menuWidget->AddToViewport();}
		PC->SetShowMouseCursor(true);
		PC->SetInputMode(FInputModeUIOnly());

		_menuWidget->OnStart.AddUniqueDynamic(this,&AGameMode::StartMatch);
		

	}
}

void AC4EGameMode::Restart()
{
	SetMatchState(MatchState::WaitingToStart);
}

