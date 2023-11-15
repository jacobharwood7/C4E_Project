// Fill out your copyright notice in the Description page of Project Settings.


#include "C4EGameMode.h"

#include "C4EAICharacter.h"
#include "C4EPlayerController.h"
#include "GameRule.h"
#include "Blueprint/UserWidget.h"
#include "WidgetMainMenu.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

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
		castedPC ->Init();
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
	if(_gameRulesLeft!=0){return;}
	EndMatch();
	
	
}

void AC4EGameMode::Handle_GameRulePointsScored(AController* scorer, int points)
{
	
	UE_LOG(LogTemp,Display,TEXT("POINT to gryffindor"))
	AC4EPlayerController* castedPC = Cast<AC4EPlayerController>(scorer);
	if(castedPC)
	{
		castedPC->AddScore(points);
	}
}

void AC4EGameMode::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void AC4EGameMode::HandleMatchIsWaitingToStart()
{
	
	//create main menu widget
	if(_menuWidgetClass)
	{
		AC4EPlayerController* PC = Cast<AC4EPlayerController>(_playerControllers[0]);
		PC->SetInitialLocationAndRotation(menuPoint->GetActorLocation(),menuPoint->GetActorRotation());
		_menuWidget = CreateWidget<UWidgetMainMenu,AC4EPlayerController*>(PC,_menuWidgetClass);
		_menuWidget->AddToViewport();
		PC->SetShowMouseCursor(true);
		PC->SetInputMode(FInputModeUIOnly());

		_menuWidget->OnStart.AddUniqueDynamic(this,&AGameMode::StartMatch);
	}
	UE_LOG(LogTemp,Display,TEXT("Waitingtostart"));
	Super::HandleMatchIsWaitingToStart();
}

void AC4EGameMode::HandleMatchHasStarted()
{
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
	for(AController*controller:_playerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller,UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchStarted(controller);
		}
	}
	
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
