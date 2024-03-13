// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


class AWeapon_Base;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BEANSPELLS_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TSubclassOf<AWeapon_Base>> _inventory;
	
	UInventory();

protected:
	virtual void BeginPlay() override;

	
	void AddToInventory(AWeapon_Base* item);
	void RemoveFromInventoy(AWeapon_Base* item);
	
};
