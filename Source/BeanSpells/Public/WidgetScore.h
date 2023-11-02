#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "WidgetScore.generated.h"

class UTextBlock;
UCLASS(Abstract, BlueprintType)
class BEANSPELLS_API UWidgetScore : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void UpdateScore(int score);
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;
};
