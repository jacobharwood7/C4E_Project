// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "UObject/Interface.h"
#include "Interface_Input.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInterface_Input : public UInterface
{
	GENERATED_BODY()
};
class BEANSPELLS_API IInterface_Input
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Move(const FInputActionValue& Input);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Look(const FInputActionValue& Input);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Shoot();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Jump();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopJump();
};
