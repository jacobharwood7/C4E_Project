#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCollectedSignature, class ACollectable*, subject, AController*, causer);


class USphereComponent;

UCLASS(Abstract)
class BEANSPELLS_API ACollectable : public AActor
{
	GENERATED_BODY()

public:
	ACollectable();
	
	UPROPERTY(BlueprintAssignable)
	FCollectedSignature OnCollected;

	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int _pointsValue;
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<USphereComponent> _collision;

	
	UFUNCTION(BlueprintCallable)
	void BroadcastCollected(AController* causer);

};
