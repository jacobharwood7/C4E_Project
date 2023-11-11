// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C4EAIController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Sight;

UCLASS()
class BEANSPELLS_API AC4EAIController : public AAIController
{
	GENERATED_BODY()
	
	
protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UAISenseConfig_Sight> sightConfig;

	AC4EAIController();
	
	UFUNCTION()
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void SetUpPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus stimulus);
	
};
