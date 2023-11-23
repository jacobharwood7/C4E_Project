// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetWheel.generated.h"

class UButton;
/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class BEANSPELLS_API UWidgetWheel : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void Resume();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> _left;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> _right;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> _up;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> _down;
	
};
