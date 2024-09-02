#include "WeaponManagerComponent.h"

#include "PlayerCharacter.h"
#include "WeaponComponent.h"

#include <EnhancedInputComponent.h>
#include <InputActionValue.h>

UWeaponManagerComponent::UWeaponManagerComponent() {
    
    PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponManagerComponent::BeginPlay() {

    Super::BeginPlay();

    weapons.Empty();
    currWeaponIndex = 0;

    m_character = Cast<APlayerCharacter>(GetOwner());

    for (int i = 0; i < weaponClasses.Num(); i++) {

        TSubclassOf<UWeaponComponent> weaponClass = weaponClasses[i];

        UActorComponent* component = GetOwner()->AddComponentByClass(weaponClass, true, FTransform(FQuat::Identity, FVector::Zero(), FVector(0.25f, 0.1f, 0.1f)), false);
        UWeaponComponent* weaponComponent = Cast<UWeaponComponent>(component);
        GetOwner()->AddInstanceComponent(weaponComponent);

        FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
        weaponComponent->AttachToComponent(this, rules);

        weaponComponent->SetVisibility(false);
        
        weapons.Add(weaponComponent);

    }

    weapons[currWeaponIndex]->SetVisibility(true);
    
}

void UWeaponManagerComponent::SetupInput(UEnhancedInputComponent* inputComponent) {

    inputComponent->BindAction(fireAction, ETriggerEvent::Triggered, this, &UWeaponManagerComponent::Fire);
    inputComponent->BindAction(reloadAction, ETriggerEvent::Triggered, this, &UWeaponManagerComponent::Reload);
    inputComponent->BindAction(cycleAction, ETriggerEvent::Triggered, this, &UWeaponManagerComponent::CycleWeapons);

}

void UWeaponManagerComponent::SelectWeapon(uint8 index) {

    if (index >= weapons.Num()) return;
    
    weapons[currWeaponIndex]->SetVisibility(false);
    weapons[index]->SetVisibility(true);
    currWeaponIndex = index;

}

void UWeaponManagerComponent::Fire(const FInputActionValue& actionValue) {

    if (currWeaponIndex >= weapons.Num()) return;

    weapons[currWeaponIndex]->Fire(m_character);

}
void UWeaponManagerComponent::Reload(const FInputActionValue& actionValue) {

    if (currWeaponIndex >= weapons.Num()) return;

    weapons[currWeaponIndex]->Reload();

}
void UWeaponManagerComponent::CycleWeapons(const FInputActionValue& actionValue) {

    int8 index = currWeaponIndex + (int8) actionValue.Get<float>();

    if (index < 0)
        index = weapons.Num() - 1;
    else if (index >= weapons.Num())
        index = 0;

    SelectWeapon(index);
    currWeaponIndex = (uint8) index;
    
}