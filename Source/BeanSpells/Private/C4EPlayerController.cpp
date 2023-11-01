#include "C4EPlayerController.h"

#include "C4ECharacter.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"


AC4EPlayerController::AC4EPlayerController() : Super()
{
	
}

void AC4EPlayerController::Init_Implementation()
{
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(_defaultMappingContext, 0);
	}

	if(GetPawn()!=nullptr)
	{
		GetPawn()->Destroy();
	}
}

void AC4EPlayerController::Handle_MatchStarted_Implementation()
{
	UWorld* const World = GetWorld();
	AActor* TempStart = UGameplayStatics::GetGameMode(World)->FindPlayerStart(this);
	FVector spawnLocation = TempStart!=nullptr ? TempStart->GetActorLocation():FVector::ZeroVector;
	FRotator spawnRotation = TempStart!=nullptr ? TempStart->GetActorRotation():FRotator::ZeroRotator;
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APawn* tempPawn = World->SpawnActor<APawn>(_pawnToSpawn,spawnLocation,spawnRotation,spawnParams);
	Possess(tempPawn);
	if(AC4ECharacter* castedPawn = Cast<AC4ECharacter>(tempPawn))
	{
		//TODO: Bind to any relevant events
		castedPawn->Init();
	}

	IMatchStateHandler::Handle_MatchStarted_Implementation();
}

void AC4EPlayerController::Handle_MatchEnded_Implementation()
{
	//SetInputMode(FInputModeUIOnly());
}
