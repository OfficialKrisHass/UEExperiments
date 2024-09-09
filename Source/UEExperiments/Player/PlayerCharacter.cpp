#include "PlayerCharacter.h"

#include "Weapon/WeaponmanagerComponent.h"

#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>

#include <EnhancedInputComponent.h>
#include <InputActionValue.h>

DEFINE_LOG_CATEGORY(LogCharacter);

APlayerCharacter::APlayerCharacter() {

	PrimaryActorTick.bCanEverTick = false;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(GetCapsuleComponent());
	camera->SetRelativeLocation(FVector(-10.0f, 0.0f, 60.0f));
	camera->bUsePawnControlRotation = true;

	weaponManager = CreateDefaultSubobject<UWeaponManagerComponent>(TEXT("Weapon manager"));
	weaponManager->SetupAttachment(camera);
	weaponManager->SetRelativeLocation(FVector(40.0f, 15.0f, -30.0f));

}

void APlayerCharacter::BeginPlay() {

	Super::BeginPlay();

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent) {

	Super::SetupPlayerInputComponent(playerInputComponent);

	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(playerInputComponent);
	if (inputComponent == nullptr) {

		UE_LOG(LogCharacter, Error, TEXT("Failed to cast UInputComponent to UEnhancedInputComponent in APlayerCharacter::SetupPlayerInputComponent()"));
		return;

	}

	inputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	inputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

	weaponManager->SetupInput(inputComponent);

}

void APlayerCharacter::Move(const FInputActionValue& actionValue) {

	if (Controller == nullptr) return;

	FVector2D value = actionValue.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), value.X);
	AddMovementInput(GetActorRightVector(), value.Y);

}
void APlayerCharacter::Look(const FInputActionValue& actionValue) {

	if (Controller == nullptr) return;

	FVector2d value = actionValue.Get<FVector2D>();

	AddControllerYawInput(value.X);
	AddControllerPitchInput(value.Y);

}