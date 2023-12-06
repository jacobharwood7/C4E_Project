
#include "Components/Health.h"

UHealth::UHealth()
{
	PrimaryComponentTick.bCanEverTick = true;
	_maxHealth=100.0f;

}


void UHealth::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this,&UHealth::DamageTaken);

	_currentHealth = _maxHealth;
	
}

void UHealth::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType,
                          AController* instigator, AActor* causer)
{
	float change = FMath::Min(_currentHealth,damage);
	_currentHealth -= change;
	OnDamaged.Broadcast(_currentHealth);
	if(_currentHealth<=0.0f){OnDead.Broadcast(instigator);}
}