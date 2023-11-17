﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "C4EAIController.h"

#include "C4EAICharacter.h"
#include "C4ECharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"


AC4EAIController::AC4EAIController()
{
	SetUpPerceptionSystem();
}

void AC4EAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AC4EAICharacter* AI = Cast<AC4EAICharacter>(InPawn))
	{
		AI->Init_Implementation();
		UBlackboardComponent* bc;
		UseBlackboard(AI->GetBehaviourTree()->BlackboardAsset,bc);
		Blackboard = bc;
		RunBehaviorTree(AI->GetBehaviourTree());
		
	}
}

void AC4EAIController::SetUpPerceptionSystem()
{
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	
	if(sightConfig)
	{
		UE_LOG(LogTemp, Display,TEXT("Perception System created"));
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		sightConfig->SightRadius = 2000.0f;//how far ai can see
		sightConfig->LoseSightRadius = sightConfig->SightRadius+500.0f;//how far player must be to not be seen
		sightConfig->PeripheralVisionAngleDegrees=90.0f;//fov of the ai.
		sightConfig->SetMaxAge(5.0f);//time after the perceived stimulus is forgotten, ie looks again;
		sightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;//continue to see stimulus if stays within range of last seen location but can't actually see
		sightConfig->DetectionByAffiliation.bDetectEnemies =true;//which types of stimulus is detected.
		sightConfig->DetectionByAffiliation.bDetectNeutrals =true;
		sightConfig->DetectionByAffiliation.bDetectFriendlies =true;
		
		GetPerceptionComponent()->SetDominantSense(*sightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddUniqueDynamic(this,&AC4EAIController::OnTargetDetected);//bind event to update when something is seen
		GetPerceptionComponent()->ConfigureSense(*sightConfig);//set up sight system
	}
}

void AC4EAIController::OnTargetDetected(AActor* Actor, FAIStimulus stimulus)
{
	if(AC4ECharacter* PP = Cast<AC4ECharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", stimulus.WasSuccessfullySensed());
	}
}

void AC4EAIController::Handle_MatchStarted_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(_TimerSpawnerHandle,this,&AC4EAIController::SpawnAI,_spawnRate,true);
	IMatchStateHandler::Handle_MatchStarted_Implementation();
}

void AC4EAIController::Handle_MatchEnded_Implementation()
{
	IMatchStateHandler::Handle_MatchEnded_Implementation();
}

void AC4EAIController::SpawnAI()
{
	UWorld* const World = GetWorld();
	UGameplayStatics::GetAllActorsWithTag(World,FName("AISpawn"),_spawnPoints);
	FVector spawnLocation = _spawnPoints[FMath::RandRange(0,_spawnPoints.Num())]->GetActorLocation();
	FRotator spawnRotation = _spawnPoints[FMath::RandRange(0,_spawnPoints.Num())]->GetActorRotation();
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	_AIPawn = World->SpawnActor<APawn>(_pawnToSpawn,spawnLocation,spawnRotation,spawnParams);
	Possess(_AIPawn);
	if(AC4EAICharacter* castedPawn = Cast<AC4EAICharacter>(_AIPawn))
	{
		//TODO: Bind to any relevant events
		castedPawn->Init();
	}
	
}


