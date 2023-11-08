#pragma once

#include "CoreMinimal.h"
#include "MatchStateHandler.h"
#include "GameFramework/PlayerController.h"
#include "C4EPlayerController.generated.h"

class UWidgetPause;
class UWidgetScore;
class UInputMappingContext;

UCLASS(Abstract)
class BEANSPELLS_API AC4EPlayerController : public APlayerController, public IMatchStateHandler
{
	GENERATED_BODY()
public:
	AC4EPlayerController();

	UFUNCTION(BlueprintNativeEvent)
	void Init();

	virtual void Handle_MatchStarted_Implementation() override;
	virtual void Handle_MatchEnded_Implementation() override;

	UFUNCTION()
	void Handle_Paused();
	

	void AddScore(int amount);
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> _pawnToSpawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetScore> _scoreWidgetClass;
	TObjectPtr<UWidgetScore> _scoreWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetPause> _pauseWidgetClass;
	TObjectPtr<UWidgetPause> _pauseWidget;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input",meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> _defaultMappingContext;

	int _score;
};
