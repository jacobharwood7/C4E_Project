// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRuleCollectables.generated.h"

class ACollectable;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BEANSPELLS_API UGameRuleCollectables : public UGameRule
{
	GENERATED_BODY()

public:
	UGameRuleCollectables();

	virtual void Init() override;

	UFUNCTION()
	void Handle_Collected(ACollectable* subject, AController* causer);
	UFUNCTION()
	void Handle_Spawn(ACollectable* subject);
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TObjectPtr<ACollectable>> _allCollectables;

	int _amountRemaining;
	
};
