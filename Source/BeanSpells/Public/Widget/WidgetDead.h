// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetDead.generated.h"

class UButton;
class FName;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReturnSignature);
UCLASS()
class BEANSPELLS_API UWidgetDead : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void ReturnButton();
	UFUNCTION()
	void QuitButton();

	FReturnSignature OnReturn;
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> _return;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> _quit;
};
