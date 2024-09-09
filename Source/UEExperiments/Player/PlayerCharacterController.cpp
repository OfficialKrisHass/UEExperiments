#include "PlayerCharacterController.h"

#include <EnhancedInputSubsystems.h>
#include <Engine/LocalPlayer.h>

void APlayerCharacterController::BeginPlay() {

    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
        subsystem->AddMappingContext(mappingContext, 0);

}