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

    BroadcastCurrentStats();
    
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

void UWeaponManagerComponent::BroadcastCurrentStats() {

    UWeaponComponent* weapon = weapons[currWeaponIndex];

    onAmmoUpdated.Broadcast(weapon->ammo, weapon->ammo, weapon->mags, weapon->mags);

}

void UWeaponManagerComponent::Fire(const FInputActionValue& actionValue) {

    if (currWeaponIndex >= weapons.Num()) return;

    UWeaponComponent* weapon = weapons[currWeaponIndex];
    if (weapon->ammo == 0) return;

    uint8 oldAmmo = weapon->ammo;
    weapon->Fire(m_character);

    onAmmoUpdated.Broadcast(oldAmmo, weapon->ammo, weapon->mags, weapon->mags);

}
void UWeaponManagerComponent::Reload(const FInputActionValue& actionValue) {

    if (currWeaponIndex >= weapons.Num()) return;

    UWeaponComponent* weapon = weapons[currWeaponIndex];
    if (weapon->ammo == weapon->magSize || weapon->mags == 0) return;

    uint8 oldAmmo = weapon->ammo;
    uint8 oldMags = weapon->mags;
    weapon->Reload();
    
    onAmmoUpdated.Broadcast(oldAmmo, weapon->ammo, oldMags, weapon->mags);

}
void UWeaponManagerComponent::CycleWeapons(const FInputActionValue& actionValue) {

    int8 index = currWeaponIndex + (int8) actionValue.Get<float>();

    if (index < 0)
        index = weapons.Num() - 1;
    else if (index >= weapons.Num())
        index = 0;

    SelectWeapon(index);

    onAmmoUpdated.Broadcast(weapons[currWeaponIndex]->ammo, weapons[index]->ammo, weapons[currWeaponIndex]->mags, weapons[index]->mags);

    currWeaponIndex = (uint8) index;
    
}