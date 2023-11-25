// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WidgetWheel.h"

#include "Components/Button.h"
#include "Components/Inventory.h"
#include "Kismet/GameplayStatics.h"
#include "Player/C4ECharacter.h"
#include "Player/C4EPlayerController.h"
#include "Weapons/Weapon_Base.h"

void UWidgetWheel::NativeConstruct()
{
	Super::NativeConstruct();

	if(_left)
	{		
		_left->OnClicked.AddUniqueDynamic(this,&UWidgetWheel::WeaponSwitch);
	}
	if(_right)
	{		
		_right->OnClicked.AddUniqueDynamic(this,&UWidgetWheel::WeaponSwitch);
	}
	if(_up)
	{		
		_up->OnClicked.AddUniqueDynamic(this,&UWidgetWheel::WeaponSwitch);
	}
	if(_down)
	{		
		_down->OnClicked.AddUniqueDynamic(this,&UWidgetWheel::WeaponSwitch);
	}

	PC = Cast<AC4EPlayerController>(GetOwningPlayer());
	
	
}
void UWidgetWheel::WeaponSwitch()
{
	
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Black,TEXT("SWITCH ATTEMPT PRESS"));
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(),1.0f);
	
	PC->SetShowMouseCursor(false);
	PC->SetInputMode(FInputModeGameOnly());

	AC4ECharacter* Player = Cast<AC4ECharacter>(PC->GetPawn());
	
	for(TSubclassOf<AWeapon_Base> Weapon : PC->_playerInv->_inventory)
	{
		
		if(Weapon->GetDefaultObject<AWeapon_Base>()->_icon == Cast<UTexture2D>(_upImg))
		{
			Player->_CurrentWeapon = PC->_playerInv->_inventory[0];
		}
	}

	RemoveFromParent();
}
