#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponManagerComponent.generated.h"

class UEnhancedInputComponent;
class UInputAction;
struct FInputActionValue;

class APlayerCharacter;
class UWeaponComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FAmmoUpdated, uint8, oldAmmo, uint8, newAmmo, uint8, oldMags, uint8, newMags);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEEXPERIMENTS_API UWeaponManagerComponent : public USceneComponent {

	GENERATED_BODY()

public:
	UWeaponManagerComponent();

	UPROPERTY(BlueprintAssignable) FAmmoUpdated onAmmoUpdated;

	void SetupInput(UEnhancedInputComponent* inputComponent);

	void SelectWeapon(uint8 index);

	UFUNCTION() void BroadcastCurrentStats();
	

private:
	UPROPERTY(EditAnywhere) TArray<TSubclassOf<UWeaponComponent>> weaponClasses;

	UPROPERTY(VisibleAnywhere) uint8 currWeaponIndex = 0;
	UPROPERTY(VisibleAnywhere) TArray<UWeaponComponent*> weapons;

	UPROPERTY(EditAnywhere, Category="Input") UInputAction* fireAction;
	UPROPERTY(EditAnywhere, Category="Input") UInputAction* reloadAction;
	UPROPERTY(EditAnywhere, Category="Input") UInputAction* cycleAction;

	UPROPERTY() APlayerCharacter* m_character = nullptr;

	virtual void BeginPlay() override;

	void Fire(const FInputActionValue& actionValue);
	void Reload(const FInputActionValue& actionValue);
	void CycleWeapons(const FInputActionValue& actionValue);
	
};