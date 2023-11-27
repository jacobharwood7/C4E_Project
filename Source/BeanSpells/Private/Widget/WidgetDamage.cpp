// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WidgetDamage.h"

#include "Components/TextBlock.h"

void UWidgetDamage::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetDamage::Damage(int points)
{
	if(_damageText)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Turquoise,TEXT("DAMAGE FIRED"));
		_damageText->SetText(FText::FromString(FString::FromInt(points)));
		PlayAnimation(_fadeAnim);
		
	}
}
