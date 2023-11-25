// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "Projectile.h"
#include "ProjectileWeapon.generated.h"

UCLASS()
class BEANSPELLS_API AProjectileWeapon : public AWeapon_Base
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> _projectile;

public:
	virtual bool Fire_Implementation() override;

};
