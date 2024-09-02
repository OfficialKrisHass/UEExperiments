#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponComponent.generated.h"

class UEnhancedInputComponent;

class UInputAction;
struct FInputActionValue;

class APlayerCharacter;
class UWeaponManagerComponent;

UCLASS()
class UEEXPERIMENTS_API UWeaponComponent : public UStaticMeshComponent {

	GENERATED_BODY()

	friend UWeaponManagerComponent;

public:
	UWeaponComponent();

	uint8 GetAmmo() { return ammo; }
	
private:
	UPROPERTY(EditAnywhere, Category="Ammo") uint8 ammo = 10;
	UPROPERTY(EditAnywhere, Category="Ammo") uint8 mags = 3;
	UPROPERTY(EditAnywhere, Category="Ammo") uint8 magSize = 10;

	UPROPERTY(EditAnywhere) float damage = 30.0f;
	UPROPERTY(EditAnywhere) float impactStrength = 10.0f;
	UPROPERTY(EditAnywhere) USoundBase* fireSound;

	virtual void BeginPlay() override;

	void Fire(APlayerCharacter* m_character);
	void Reload(APlayerCharacter* m_character);
	
};
