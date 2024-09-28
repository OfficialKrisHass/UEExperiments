#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "AmmoPickup.generated.h"

class UWeaponComponent;

UCLASS()
class UEEXPERIMENTS_API AAmmoPickup : public APickupBase {

	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere) TSubclassOf<UWeaponComponent> weapon = 0;
	UPROPERTY(EditAnywhere) uint8 mags = 0;

	virtual void OnPickup(TObjectPtr<APlayerCharacter> player) override;
	
};
