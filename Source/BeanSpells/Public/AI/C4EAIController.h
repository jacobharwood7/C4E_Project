// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interfaces/MatchStateHandler.h"
#include "C4EAIController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Sight;

UCLASS()
class BEANSPELLS_API AC4EAIController : public AAIController, public IMatchStateHandler
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UAISenseConfig_Sight> sightConfig;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> _spawnPoints;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> _pawnToSpawn;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APawn> _AIPawn;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _spawnRate;

	FTimerHandle _TimerSpawnerHandle;
	
	AC4EAIController();
	
	UFUNCTION()
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void SetUpPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus stimulus);

	UFUNCTION()
	virtual void Handle_MatchStarted_Implementation() override;
	virtual void Handle_MatchEnded_Implementation() override;

};
