// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetDamage.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class BEANSPELLS_API UWidgetDamage : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void Damage(int points);
private:
	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<UTextBlock> _damageText;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> _fadeAnim;
};
