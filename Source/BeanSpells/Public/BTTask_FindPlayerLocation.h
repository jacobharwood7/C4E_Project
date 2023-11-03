// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class BEANSPELLS_API UBTTask_FindPlayerLocation : public UBTTask_BlackboardBase
{
public:
	explicit UBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInit);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Search", meta=(AllowPrivateAccess="true"))
	bool _searchRandom = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Search",meta=(AllowPrivateAccess="true"))
	float _searchRadius = 150.0f;
};