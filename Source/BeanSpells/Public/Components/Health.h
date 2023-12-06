// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"

class UWidgetComponent;
class UWidgetDamage;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FComponentDeadSignature, AController*, causer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FComponentDamagedSignature, float, newhealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BEANSPELLS_API UHealth : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UHealth();



	UPROPERTY(BlueprintAssignable,Category = "Components")
	FComponentDeadSignature OnDead;
	UPROPERTY(BlueprintAssignable,Category = "Components")
	FComponentDamagedSignature OnDamaged;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Health")
	float _maxHealth;
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Health")
	float _currentHealth;
	
	virtual void BeginPlay() override;

	
	UFUNCTION()
	void DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* causer);

};
