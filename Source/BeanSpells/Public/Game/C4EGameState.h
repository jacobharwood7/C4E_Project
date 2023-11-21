﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "C4EGameState.generated.h"

UCLASS(Abstract)
class BEANSPELLS_API AC4EGameState : public AGameState
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC4EGameState();

	int GetRoundNum();
	void IncrementRound();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int _roundNum;
	int _deathEaterOnMap;
	

};
