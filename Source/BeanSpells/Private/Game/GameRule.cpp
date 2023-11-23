#include "Game/GameRule.h"

UGameRule::UGameRule()
{
	_isOptional = false;
}

void UGameRule::Init()
{
}

void UGameRule::BroadcastGameRuleCompleted()
{
	OnGameRuleCompleted.Broadcast(this);
}

void UGameRule::BroadcastGameRulePointsScored(AController* scorer, int points,int type)
{
	OnGameRulePointsScored.Broadcast(scorer,points,type);
}
