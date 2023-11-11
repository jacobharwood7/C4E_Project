#pragma once

#include "CoreMinimal.h"
#include "MatchStateHandler.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "C4EPlayerController.generated.h"

class AC4ECharacter;
class UWidgetPause;
class UWidgetScore;
class UInputAsset;

UCLASS(Abstract)
class BEANSPELLS_API AC4EPlayerController : public APlayerController, public IMatchStateHandler
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSoftObjectPtr<UInputAsset> _inputActions;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> _pawnToSpawn;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input",meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> _mappingContext;


	void Move(const FInputActionValue& Input);
	void Look(const FInputActionValue& Input);
	void Shoot();
	void Jump();
	void StopJump();
	
	AC4EPlayerController();

	UFUNCTION(BlueprintNativeEvent)
	void Init();

	UFUNCTION()
	virtual void SetupInputComponent() override;

	virtual void Handle_MatchStarted_Implementation() override;
	virtual void Handle_MatchEnded_Implementation() override;

	UFUNCTION()
	void Handle_Paused();

	void AddScore(int amount);
	
protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetScore> _scoreWidgetClass;
	TObjectPtr<UWidgetScore> _scoreWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetPause> _pauseWidgetClass;
	TObjectPtr<UWidgetPause> _pauseWidget;
	
	int _score;
};
