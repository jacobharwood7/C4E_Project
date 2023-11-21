// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponType.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BEANSPELLS_API UWeaponType : public UDataAsset
{
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _damage;
};
