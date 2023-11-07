#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"

#include "WidgetPause.generated.h"

class UTextBlock;
UCLASS(Abstract, BlueprintType)
class BEANSPELLS_API UWidgetPause : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
};
