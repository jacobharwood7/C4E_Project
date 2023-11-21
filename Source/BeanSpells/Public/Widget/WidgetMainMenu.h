// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetMainMenu.generated.h"

class UButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartSignature);

UCLASS(Abstract,BlueprintType)
class BEANSPELLS_API UWidgetMainMenu : public UUserWidget
{	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void PlayButton();
	UFUNCTION()
	void QuitButton();

	FStartSignature OnStart;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> playgame;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> quitgame;
	
};
