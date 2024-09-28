#include "AmmoPickup.h"

#include "../Weapon/WeaponManagerComponent.h"

#include "../Player/PlayerCharacter.h"

void AAmmoPickup::OnPickup(TObjectPtr<APlayerCharacter> player) {
    
    player->GetWeaponManagerComponent()->AddWeaponMags(weapon, mags);

}