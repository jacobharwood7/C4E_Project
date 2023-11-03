// Fill out your copyright notice in the Description page of Project Settings.


#include "C4EAIController.h"

#include "C4EAICharacter.h"


AC4EAIController::AC4EAIController()
{
	
}

void AC4EAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AC4EAICharacter* AI = Cast<AC4EAICharacter>(InPawn))
	{
		RunBehaviorTree(AI->_behaviourTree);
	}
}


