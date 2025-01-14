﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetWheel.generated.h"

class AC4EPlayerController;
class UImage;
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
	void WeaponSwitch(FString button);
	UFUNCTION()
	void LeftPressed();
	UFUNCTION()
	void RightPressed();
	UFUNCTION()
	void UpPressed();
	UFUNCTION()
	void DownPressed();
	virtual FReply NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	
	TObjectPtr<AC4EPlayerController> PC;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> _left;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> _right;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> _up;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> _down;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> _leftImg;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> _rightImg;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> _upImg;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> _downImg;

	
};
