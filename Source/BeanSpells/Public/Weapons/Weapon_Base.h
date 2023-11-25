// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Interfaces/Fireable.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"

class UImage;
class UWeaponType;
class UArrowComponent;

UCLASS(Abstract)
class BEANSPELLS_API AWeapon_Base : public AActor, public IFireable
{
	GENERATED_BODY()

	
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UTexture2D> _icon;
	
	AWeapon_Base();

	virtual bool Fire_Implementation() override;

	void Init(UWeaponType* type);
	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;
	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> _Mesh;
	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Muzzle;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UWeaponType> _typeData;
};
