// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WidgetMainMenu.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UWidgetMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	if(playgame)
	{		
		playgame->OnClicked.AddUniqueDynamic(this,&UWidgetMainMenu::PlayButton);
	}
	if(quitgame)
	{
		quitgame->OnClicked.AddUniqueDynamic(this,&UWidgetMainMenu::QuitButton);
	}
}

void UWidgetMainMenu::PlayButton()
{
	//start match and destroy main menu
	APlayerController* PC = GetOwningPlayer();
	
	PC->SetShowMouseCursor(false);
	PC->SetInputMode(FInputModeGameOnly());

	RemoveFromParent();
	OnStart.Broadcast();
}

void UWidgetMainMenu::QuitButton()
{
	APlayerController* PC = GetOwningPlayer();
	UKismetSystemLibrary::QuitGame(GetWorld(),PC,EQuitPreference::Quit,false);
}
