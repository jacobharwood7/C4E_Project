// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetCoins.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class BEANSPELLS_API UWidgetCoins : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void UpdateCoins(int coins);
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CoinText;
};
