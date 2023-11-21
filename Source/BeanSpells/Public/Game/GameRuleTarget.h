// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "Components/ActorComponent.h"
#include "GameRuleTarget.generated.h"

class UTarget;

UCLASS

(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BEANSPELLS_API UGameRuleTarget : public UGameRule
{
	GENERATED_BODY()

public:
	UGameRuleTarget();

	virtual void Init() override;
	
	void Handle_TargetSpawned(UTarget* spawned);
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TObjectPtr<UTarget>> _targets;
	int _amountRemaining;

	UFUNCTION()
	void Handle_TargetDestroyed(AActor* target, AController* causer);
};
