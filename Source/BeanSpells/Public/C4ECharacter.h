// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "C4ECharacter.generated.h"


class UWeaponType;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AWeapon_Base;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPause);

UCLASS(Abstract)
class BEANSPELLS_API AC4ECharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta =(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> _camera;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta =(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> _weaponAttachPoint;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	UInputAction* ShootAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	UInputAction* PauseAction;


public:
	AC4ECharacter();
	UFUNCTION(BlueprintNativeEvent)
	void Init();

	FPause OnPause;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _CurrentWeapon;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<AActor> _FireableRef;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);

	void Shoot();
	void Pause();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
