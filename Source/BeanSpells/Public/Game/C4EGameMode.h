﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "C4EGameMode.generated.h"

class UWidgetDead;
class AC4EAIController;
class AC4EAICharacter;
class UWidgetMainMenu;
class UGameRule;

UCLASS(Abstract)
class BEANSPELLS_API AC4EGameMode : public AGameMode
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<AActor> menuPoint;
	TSoftObjectPtr<AActor> spawnPoint;
	
	
	AC4EGameMode();

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AC4EAICharacter> AIPawn;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> _spawnPoints;
	
	FTimerHandle _TimerSpawnerHandle;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetMainMenu> _menuWidgetClass;
	TObjectPtr<UWidgetMainMenu> _menuWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetDead> _deathWidgetClass;
	TObjectPtr<UWidgetDead> _deathWidget;
	
	TArray<TObjectPtr<AActor>> _playerStarts;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _playerControllers;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "MatchManage")
	int _countdownTimer;

	int _gameRulesLeft;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<TObjectPtr<UGameRule>, bool> _gameRuleManagers;

	UFUNCTION()
	void Handle_GameRuleCompleted(UGameRule* rule);
	
	UFUNCTION()
	void Handle_GameRulePointsScored(AController* scorer, int points, int type);

	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
	
	virtual void OnMatchStateSet() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;

	void SpawnAI();
	UFUNCTION()
	void SetUpMenu();
	UFUNCTION()
	void Restart();
};
