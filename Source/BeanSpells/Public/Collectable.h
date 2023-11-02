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
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<USphereComponent> _collision;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult,AController* control);

	UFUNCTION(BlueprintCallable)
	void BroadcastCollected(AController* causer);

};
