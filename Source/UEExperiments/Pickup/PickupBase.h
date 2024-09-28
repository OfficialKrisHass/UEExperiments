#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class APlayerCharacter;

class UWeaponManagerComponent;

class UStaticMeshComponent;
class UBoxComponent;

UCLASS(Abstract)
class UEEXPERIMENTS_API APickupBase : public AActor {

	GENERATED_BODY()
	
public:
	APickupBase();

private:
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UBoxComponent> trigger = nullptr;

	virtual void BeginPlay() override;

	virtual void OnPickup(TObjectPtr<APlayerCharacter> player) {}

	UFUNCTION()
    void BeginOverlap(UPrimitiveComponent* overllapedComp, AActor* actor, UPrimitiveComponent* otherComp, int32 otherIndex, bool fromSweep, const FHitResult& sweepResult);
	
};