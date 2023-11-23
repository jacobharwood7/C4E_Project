// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WidgetCoins.h"

#include "Components/TextBlock.h"

void UWidgetCoins::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetCoins::UpdateCoins(int coins)
{
	if(CoinText)
	{
		CoinText->SetText(FText::FromString(FString::Printf(TEXT("%d"),coins)));
	}
}
