#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

class UEnhancedInputComponent;

class UInputAction;
struct FInputActionValue;

class APlayerCharacter;

UCLASS()
class UEEXPERIMENTS_API UWeaponComponent : public USkeletalMeshComponent {

	GENERATED_BODY()

public:
	UWeaponComponent();

	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;

	void Attach(APlayerCharacter* character, UEnhancedInputComponent* inputComponent);

private:
	UPROPERTY(EditAnywhere) float damage = 30.0f;
	UPROPERTY(EditAnywhere) float impactStrength = 10.0f;

	UPROPERTY(EditAnywhere) UInputAction* fireAction;
	UPROPERTY(EditAnywhere) USoundBase* fireSound;

	UPROPERTY() APlayerCharacter* m_character;

	virtual void BeginPlay() override;

	void Fire(const FInputActionValue& actionValue);
	
};
