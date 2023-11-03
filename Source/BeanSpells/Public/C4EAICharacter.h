#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "C4EAICharacter.generated.h"


class UWeaponType;
class UInputMappingContext;
class UInputAction;
class AWeapon_Base;
class UBehaviorTree;


UCLASS(Abstract)
class BEANSPELLS_API AC4EAICharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta =(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> _weaponAttachPoint;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	
public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "AI")
	UBehaviorTree* _behaviourTree;
	
	AC4EAICharacter();

	UFUNCTION(BlueprintNativeEvent)
	void Init();
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _CurrentWeapon;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UWeaponType> _DefaultWeaponType;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<AActor> _FireableRef;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);

	void Shoot();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
};
