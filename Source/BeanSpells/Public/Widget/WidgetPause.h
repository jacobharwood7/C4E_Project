#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "WidgetPause.generated.h"

class UButton;
UCLASS(Abstract, BlueprintType)
class BEANSPELLS_API UWidgetPause : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void ResumeButton();
	UFUNCTION()
	void QuitButton();
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> resume;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> quit;
	
};
