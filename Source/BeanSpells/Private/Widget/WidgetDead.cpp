// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WidgetDead.h"

#include "Components/Button.h"
#include "Game/C4EGameMode.h"
#include "GameFramework/GameMode.h"
#include "Kismet/KismetSystemLibrary.h"

void UWidgetDead::NativeConstruct()
{
	Super::NativeConstruct();
	if(_return)
	{		
		_return->OnClicked.AddUniqueDynamic(this,&UWidgetDead::ReturnButton);
	}
	if(_quit)
	{
		_quit->OnClicked.AddUniqueDynamic(this,&UWidgetDead::QuitButton);
	}
}

void UWidgetDead::ReturnButton()
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("RETURN PRESSED"));
	RemoveFromParent();
	OnReturn.Broadcast();
}

void UWidgetDead::QuitButton()
{
	APlayerController* PC = GetOwningPlayer();
	UKismetSystemLibrary::QuitGame(GetWorld(),PC,EQuitPreference::Quit,false);
}
