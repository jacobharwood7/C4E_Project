#include "HitScanWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogScan, Display, All);

bool AHitScanWeapon::Fire_Implementation()
{
	_Damage = 10.0f;
	_Range = 50.0f;
	UE_LOG(LogScan,Display,TEXT("FIRING HITSCAN WEAPON CLASS"))
	UWorld* const world=GetWorld();

	if(world == nullptr){return false;}

	FHitResult Hit(ForceInit);
	FVector Origin = _Muzzle->GetComponentLocation();
	FVector End = Origin+_Muzzle->GetForwardVector()*_Range;
	

	if(UKismetSystemLibrary::LineTraceSingle(GetWorld(),Origin,End,UEngineTypes::ConvertToTraceType(ECC_Visibility)
		,true,{this,GetOwner()},EDrawDebugTrace::ForDuration,Hit,true,FLinearColor::Red,FLinearColor::Green,5.0f))
	{
		UE_LOG(LogScan, Display, TEXT("Hit position: %s"),*Hit.ImpactPoint.ToString())
		if(Hit.GetActor()->CanBeDamaged())
		{
			UGameplayStatics::ApplyDamage(Hit.GetActor(),_Damage,nullptr,this,UDamageType::StaticClass());
		}
		return true;
	}
	return false;
}
