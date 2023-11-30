// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WidgetWheel.h"

#include "EnhancedInputComponent.h"
#include "Components/Button.h"
#include "Components/Inventory.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"
#include "Player/C4ECharacter.h"
#include "Player/C4EPlayerController.h"
#include "Weapons/Weapon_Base.h"

void UWidgetWheel::NativeConstruct()
{
	Super::NativeConstruct();
	
	PC = Cast<AC4EPlayerController>(GetOwningPlayer());
	SetIsFocusable(true);
	SetFocus();

	if(_left)
	{		
		_left->OnPressed.AddUniqueDynamic(this,&UWidgetWheel::LeftPressed);
		
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Black,TEXT("Left Button Bound"));
	}
	if(_right)
	{		
		_right->OnPressed.AddUniqueDynamic(this,&UWidgetWheel::RightPressed);
	}
	if(_up)
	{		
		_up->OnPressed.AddUniqueDynamic(this,&UWidgetWheel::UpPressed);
	}
	if(_down)
	{		
		_down->OnPressed.AddUniqueDynamic(this,&UWidgetWheel::DownPressed);
	}
	
	if(_upImg)
	{
		_upImg->SetBrushFromTexture(PC->_playerInv->_inventory[0]->GetDefaultObject<AWeapon_Base>()->_icon);
	}
	if(_leftImg)
	{		
		_leftImg->SetBrushFromTexture(PC->_playerInv->_inventory[1]->GetDefaultObject<AWeapon_Base>()->_icon);
	}
	if(_downImg)
	{		
		_downImg->SetBrushFromTexture(PC->_playerInv->_inventory[0]->GetDefaultObject<AWeapon_Base>()->_icon);
	}
	if(_rightImg)
	{		
		_rightImg->SetBrushFromTexture(PC->_playerInv->_inventory[1]->GetDefaultObject<AWeapon_Base>()->_icon);
	}
	
	
}
void UWidgetWheel::WeaponSwitch(FString button)
{
	
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(),1.0f);
	
	PC->SetShowMouseCursor(false);
	PC->SetInputMode(FInputModeGameOnly());

	AC4ECharacter* Player = Cast<AC4ECharacter>(PC->GetPawn());

	UImage* buttonImage = nullptr;
	if(button == "_left"){buttonImage = _leftImg;}
	else if(button == "_right"){buttonImage = _rightImg;}
	else if (button == "_up"){buttonImage = _upImg;}
	else if (button == "_down"){buttonImage = _downImg;}
	
	
	for(TSubclassOf<AWeapon_Base> Weapon : PC->_playerInv->_inventory)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("Item Detected"));
		
		if(Weapon->GetDefaultObject<AWeapon_Base>()->_icon == buttonImage->GetBrush().GetResourceObject())
		{
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Black,TEXT("SWITCH ATTEMPT PRESS"));
			Player->ChangeWeapon(Weapon);
		}
	}
	RemoveFromParent();
}

void UWidgetWheel::LeftPressed()
{
	FString name = _left->GetName();
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Black,FString::Printf(TEXT("button pressed, name is : %s"),*name));
	WeaponSwitch(name);
}

void UWidgetWheel::RightPressed()
{
	FString name = _right->GetName();
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Black,FString::Printf(TEXT("button pressed, name is : %s"),*name));
	WeaponSwitch(name);
}

void UWidgetWheel::UpPressed()
{
	FString name = _up->GetName();
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Black,FString::Printf(TEXT("button pressed, name is : %s"),*name));
	WeaponSwitch(name);
}

void UWidgetWheel::DownPressed()
{
	FString name = _down->GetName();
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Black,FString::Printf(TEXT("button pressed, name is : %s"),*name));
	WeaponSwitch(name);
}

FReply UWidgetWheel::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FKey Lifted = UKismetInputLibrary::GetKey(InKeyEvent);
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Black,FString::Printf(TEXT("button Lifted, name is : %s"),*Lifted.GetFName().ToString()));
	if(Lifted == "Q")
	{
		PC->Handle_FinishSwitchWeapon();
	}
	
	return Super::NativeOnKeyUp(InGeometry, InKeyEvent);
}

