#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "InputAsset.generated.h"
/**
 * 
 */
UCLASS()
class BEANSPELLS_API UInputAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> ShootAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input" ,meta =(AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> PauseAction;

};
