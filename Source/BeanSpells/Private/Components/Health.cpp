
#include "Components/Health.h"

UHealth::UHealth()
{
	PrimaryComponentTick.bCanEverTick = true;
	_maxHealth=100.0f;
	_maxShield=100.0f;
	_canRegenShield = true;
	_shieldRecoveryRate = 10.0f;
	_shieldRecoverDelay=2.0f;

}


void UHealth::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this,&UHealth::DamageTaken);

	_currentHealth = _maxHealth;
	_currentShield = 0.0f;
}

void UHealth::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType,
	AController* instigator, AActor* causer)
{
	float leftOverDamage = FMath::Max(damage - _currentShield,0.0f);
	_currentShield = FMath::Max(_currentShield-damage,0.0f);
	_shieldRecoverDelayTimer = _shieldRecoverDelay;

	if(leftOverDamage>0.0f){_currentHealth = FMath::Max(_currentHealth-leftOverDamage,0.0f);}

	if(_currentHealth<=0.0f){OnDead.Broadcast(instigator);}
}

// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if the shield is currently full or unable to regenerate then return earlier
	if(_currentShield == _maxShield||!_canRegenShield){return;}
	//skips this
	//if the delay timer hits zero then add the rate*time to current shield
	if(_shieldRecoverDelayTimer<=0.0f)
	{
		_currentShield = FMath::Min(_maxShield, _currentShield + (_shieldRecoveryRate*DeltaTime));
	}
	else//else count down timer
	{
		_shieldRecoverDelayTimer-=DeltaTime;
	}
}
