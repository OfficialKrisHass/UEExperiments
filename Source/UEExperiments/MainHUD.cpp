#include "MainHUD.h"

#include "AmmoInfo.h"
#include "MainLayout.h"

#include "WeaponManagerComponent.h"
#include "PlayerCharacter.h"

void AMainHUD::BeginPlay() {

    Super::BeginPlay();

    UWorld* world = GetWorld();

    layout = CreateWidget<UMainLayout>(world, layoutClass);
    layout->AddToViewport();
    layout->SetVisibility(ESlateVisibility::Visible);

    if (APlayerController* controller = GetOwningPlayerController()) {

        APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(controller->GetPawn());
        checkf(playerCharacter, TEXT("Unable to get the Player character"));

        weaponManager = playerCharacter->GetWeaponManagerComponent();

    }
    checkf(weaponManager, TEXT("Unable to get the Weapon Manager component"));

    weaponManager->onAmmoUpdated.AddDynamic(layout->ammoInfo, &UAmmoInfo::OnAmmoUpdated);

}