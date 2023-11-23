// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WidgetWheel.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UWidgetWheel::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(_left)
	{		
		_left->OnClicked.AddUniqueDynamic(this,&UWidgetWheel::Resume);
	}
	
}
void UWidgetWheel::Resume()
{
	
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(),1.0f);
	APlayerController* PC = GetOwningPlayer();
	
	PC->SetShowMouseCursor(false);
	PC->SetInputMode(FInputModeGameOnly());

	RemoveFromParent();
}
