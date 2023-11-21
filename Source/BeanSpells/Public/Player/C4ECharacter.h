// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interfaces/Interface_Input.h"
#include "C4ECharacter.generated.h"


class UAIPerceptionStimuliSourceComponent;
class UWeaponType;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AWeapon_Base;

UCLASS(Abstract)
class BEANSPELLS_API AC4ECharacter : public ACharacter, public IInterface_Input
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta =(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> _camera;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta =(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> _weaponAttachPoint;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	UInputMappingContext* PlayerMappingContext;


public:
	AC4ECharacter();
	UFUNCTION(BlueprintNativeEvent)
	void Init();
	virtual void Move_Implementation(const FInputActionValue& Input) override;
	virtual void Look_Implementation(const FInputActionValue& Input) override;
	virtual void Shoot_Implementation() override;
	virtual void Jump_Implementation() override;
	virtual void StopJump_Implementation() override;
	

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _CurrentWeapon;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<AActor> _FireableRef;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UAIPerceptionStimuliSourceComponent> stimSource;

	UFUNCTION()
	void SetupStimulusSource();
};
