// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerInRange.generated.h"

/**
 * 
 */
UCLASS()
class BEANSPELLS_API UBTService_PlayerInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_PlayerInRange();

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=AI,meta = (AllowPrivateAccess = "true"))
	float _spellRange = 15000.0f;
};
