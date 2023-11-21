// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "HitScanWeapon.generated.h"

UCLASS()
class BEANSPELLS_API AHitScanWeapon : public AWeapon_Base
{
	GENERATED_BODY()

public:
	virtual bool Fire_Implementation() override;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _Damage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _Range;
};
