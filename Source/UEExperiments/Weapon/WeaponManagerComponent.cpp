#include "WeaponManagerComponent.h"

#include "Player/PlayerCharacter.h"

#include "Weapon/WeaponComponent.h"

#include <EnhancedInputComponent.h>
#include <InputActionValue.h>

UWeaponManagerComponent::UWeaponManagerComponent() {
    
    PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponManagerComponent::BeginPlay() {

    Super::BeginPlay();

    weapons.Empty();
    weaponIDs.Empty();
    
    currWeaponID = 0;

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

        weaponComponent->id = weapons.Num() - 1;
        weaponIDs.Add(weaponClass, weaponComponent->id);

    }

    weapons[currWeaponID]->SetVisibility(true);

    BroadcastCurrentStats();
    
}

void UWeaponManagerComponent::SetupInput(UEnhancedInputComponent* inputComponent) {

    inputComponent->BindAction(fireAction, ETriggerEvent::Triggered, this, &UWeaponManagerComponent::Fire);
    inputComponent->BindAction(reloadAction, ETriggerEvent::Triggered, this, &UWeaponManagerComponent::Reload);
    inputComponent->BindAction(cycleAction, ETriggerEvent::Triggered, this, &UWeaponManagerComponent::CycleWeapons);

}

void UWeaponManagerComponent::SelectWeapon(TSubclassOf<UWeaponComponent> weaponClass) {

    const uint8* id = weaponIDs.Find(weaponClass);
    if (id == nullptr) return;

    SelectWeapon(*id);

}
void UWeaponManagerComponent::SelectWeapon(uint8 id) {

    if (id == 255 || id >= weapons.Num()) return;
    
    weapons[currWeaponID]->SetVisibility(false);
    weapons[id]->SetVisibility(true);
    currWeaponID = id;

}

void UWeaponManagerComponent::AddWeaponMags(TSubclassOf<UWeaponComponent> weaponClass, uint8 value) {

    uint8* id = weaponIDs.Find(weaponClass);
    if (id == nullptr) return;

    UWeaponComponent* weapon = weapons[*id];

    uint8 oldValue = weapon->mags;
    weapon->AddMags(value);

    if (*id == currWeaponID)
        onAmmoUpdated.Broadcast(weapon->ammo, weapon->ammo, oldValue, weapon->mags);

}

void UWeaponManagerComponent::BroadcastCurrentStats() {

    UWeaponComponent* weapon = weapons[currWeaponID];

    onAmmoUpdated.Broadcast(weapon->ammo, weapon->ammo, weapon->mags, weapon->mags);

}

void UWeaponManagerComponent::Fire(const FInputActionValue& actionValue) {

    if (currWeaponID >= weapons.Num()) return;

    UWeaponComponent* weapon = weapons[currWeaponID];
    if (weapon->ammo == 0) return;

    uint8 oldAmmo = weapon->ammo;
    weapon->Fire(m_character);

    onAmmoUpdated.Broadcast(oldAmmo, weapon->ammo, weapon->mags, weapon->mags);

}
void UWeaponManagerComponent::Reload(const FInputActionValue& actionValue) {

    if (currWeaponID >= weapons.Num()) return;

    UWeaponComponent* weapon = weapons[currWeaponID];
    if (weapon->ammo == weapon->magSize || weapon->mags == 0) return;

    uint8 oldAmmo = weapon->ammo;
    uint8 oldMags = weapon->mags;
    weapon->Reload();
    
    onAmmoUpdated.Broadcast(oldAmmo, weapon->ammo, oldMags, weapon->mags);

}
void UWeaponManagerComponent::CycleWeapons(const FInputActionValue& actionValue) {

    int8 newID = currWeaponID + (int8) actionValue.Get<float>();

    if (newID < 0)
        newID = weapons.Num() - 1;
    else if (newID >= weapons.Num())
        newID = 0;

    uint8 oldAmmo = weapons[currWeaponID]->ammo;
    uint8 oldMags = weapons[currWeaponID]->mags;
    SelectWeapon(newID);

    onAmmoUpdated.Broadcast(oldAmmo, weapons[newID]->ammo, oldMags, weapons[newID]->mags);
    
}