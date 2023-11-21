// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FComponentDeadSignature, AController*,causer);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BEANSPELLS_API UHealth : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UHealth();


	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable,Category = "Components")
	FComponentDeadSignature OnDead;
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Health")
	float _currentHealth;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Health")
	float _maxHealth;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Shield")
	float _currentShield;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Shield")
	float _maxShield;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Shield")
	bool _canRegenShield;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Shield")
	float _shieldRecoverDelayTimer;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Shield")
	float _shieldRecoveryRate;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Shield")
	float _shieldRecoverDelay;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* causer);

};
