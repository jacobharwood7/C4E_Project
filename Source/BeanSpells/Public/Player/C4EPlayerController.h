#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "Interfaces/MatchStateHandler.h"
#include "C4EPlayerController.generated.h"

class UInventory;
class UWidgetWheel;
class UWidgetCoins;
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
	TSubclassOf<AActor> _pawnToSpawn;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input",meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> _mappingContext;
	
	TObjectPtr<APawn> _tempPawn;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Inventory" ,meta =(AllowPrivateAccess = "true"))
	TObjectPtr<UInventory> _playerInv;
	
	void Move(const FInputActionValue& Input);
	void Look(const FInputActionValue& Input);
	void Shoot();
	void Jump();
	void StopJump();
	
	AC4EPlayerController();

	UFUNCTION(BlueprintNativeEvent)
	void Init();

	void ChangeView();
	UFUNCTION()
	virtual void SetupInputComponent() override;

	virtual void Handle_MatchStarted_Implementation() override;
	virtual void Handle_MatchEnded_Implementation() override;

	UFUNCTION()
	void Handle_Paused();

	UFUNCTION()
	void Handle_SwitchWeapon();
	void Handle_FinishSwitchWeapon();

	void AddScore(int amount);
	void AddCoin(int amount);
protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetScore> _scoreWidgetClass;
	TObjectPtr<UWidgetScore> _scoreWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetCoins> _coinWidgetClass;
	TObjectPtr<UWidgetCoins> _coinWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetPause> _pauseWidgetClass;
	TObjectPtr<UWidgetPause> _pauseWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetWheel> _wheelWidgetClass;
	TObjectPtr<UWidgetWheel> _wheelWidget;

	
	int _score;

	int _coins;
};
