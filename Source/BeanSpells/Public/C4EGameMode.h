// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "C4EGameMode.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BEANSPELLS_API AC4EGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AC4EGameMode();

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
protected:
	
	TArray<TObjectPtr<AActor>> _playerStarts;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _playerControllers;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "MatchManage")
	int _countdownTimer;
	FTimerHandle _timerDecreaseCountdown;
	UFUNCTION()
	void DecreaseCountdown();

	virtual void BeginPlay() override;

	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
	
	virtual void OnMatchStateSet() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;
};
