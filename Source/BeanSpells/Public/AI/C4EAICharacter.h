#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interface_Input.h"
#include "C4EAICharacter.generated.h"


class UTarget;
class UWeaponType;
class UInputMappingContext;
class UInputAction;
class AWeapon_Base;
class UBehaviorTree;


UCLASS(Abstract)
class BEANSPELLS_API AC4EAICharacter : public ACharacter, public IInterface_Input
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta =(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> _weaponAttachPoint;
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UTarget> _target;
	
	AC4EAICharacter();

	UFUNCTION(BlueprintNativeEvent)
	void Init();

	UBehaviorTree* GetBehaviourTree();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "AI",meta =(AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> _behaviourTree;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _CurrentWeapon;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UWeaponType> _DefaultWeaponType;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<AActor> _FireableRef;
	
	virtual void Shoot_Implementation() override;
	
};
