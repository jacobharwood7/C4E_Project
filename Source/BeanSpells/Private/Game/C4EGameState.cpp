#include "Game/C4EGameState.h"


// Sets default values
AC4EGameState::AC4EGameState()
{
	
}
void AC4EGameState::BeginPlay()
{
	Super::BeginPlay();
	
}

int AC4EGameState::GetRoundNum()
{
	return _roundNum;
}

void AC4EGameState::IncrementRound()
{
	_roundNum++;
}
