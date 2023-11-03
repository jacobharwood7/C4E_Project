// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C4EAIController.generated.h"

UCLASS()
class BEANSPELLS_API AC4EAIController : public AAIController
{
	GENERATED_BODY()
	
	
protected:
	AC4EAIController();

	UFUNCTION()
	virtual void OnPossess(APawn* InPawn) override;
	
};
