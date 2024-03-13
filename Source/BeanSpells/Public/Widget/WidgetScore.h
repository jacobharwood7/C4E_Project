#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "WidgetScore.generated.h"

class UProgressBar;
class UTextBlock;
UCLASS(Abstract, BlueprintType)
class BEANSPELLS_API UWidgetScore : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void UpdateScore(int score);
	void UpdateHealth(float newHealthRatio, float max);
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthStats;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
};
