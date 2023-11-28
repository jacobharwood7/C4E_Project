#include "Weapons/HitScanWeapon.h"

#include "Weapons/WeaponType.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogScan, Display, All);

bool AHitScanWeapon::Fire_Implementation()
{
	UWorld* const world=GetWorld();

	if(world == nullptr){return false;}

	FHitResult Hit(ForceInit);
	FVector Origin = _Muzzle->GetComponentLocation();
	FVector End = Origin+_Muzzle->GetForwardVector()*_Range;
	

	if(UKismetSystemLibrary::LineTraceSingle(GetWorld(),Origin,End,UEngineTypes::ConvertToTraceType(ECC_Visibility)
		,true,{},EDrawDebugTrace::ForDuration,Hit,true,FLinearColor::Red,FLinearColor::Green,0.3f))
	{
		
		int newDamage = FMath::RandRange(_typeData->_damage-10,_typeData->_damage+10);
		UGameplayStatics::ApplyDamage(Hit.GetActor(),newDamage,GetInstigatorController(),this,UDamageType::StaticClass());
		
		return true;
	}
	return false;
}
