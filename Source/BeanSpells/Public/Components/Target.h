// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Target.generated.h"

class UGameRuleCollectables;
class ACollectable;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetDestroyedSignature, AActor*, target, AController*,
                                             delegateInstigator);


class UHealth;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BEANSPELLS_API UTarget : public UActorComponent
{
	GENERATED_BODY()

public:

	UTarget();

	UPROPERTY(BlueprintAssignable)
	FTargetDestroyedSignature OnTargetDestroyed;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UHealth> _healthComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ACollectable> _coin;

	UGameRuleCollectables* grc;
private:
	UFUNCTION()
	void Handle_Dead(AController* causer);
	UFUNCTION()
	void SpawnCoins();
};
