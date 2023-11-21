#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "C4EGameMode.generated.h"

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

	
	FTimerHandle _TimerSpawnerHandle;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetMainMenu> _menuWidgetClass;
	TObjectPtr<UWidgetMainMenu> _menuWidget;
	
	TArray<TObjectPtr<AActor>> _playerStarts;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _playerControllers;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "MatchManage")
	int _countdownTimer;

	int _gameRulesLeft;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<TObjectPtr<UGameRule>, bool> _gameRuleManagers;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AController> AIController;
	
	FTimerHandle _timerDecreaseCountdown;
	UFUNCTION()
	void Handle_GameRuleCompleted(UGameRule* rule);
	
	UFUNCTION()
	void Handle_GameRulePointsScored(AController* scorer, int points);

	virtual void BeginPlay() override;

	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
	
	virtual void OnMatchStateSet() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;

	
	void SpawnAI();
};
