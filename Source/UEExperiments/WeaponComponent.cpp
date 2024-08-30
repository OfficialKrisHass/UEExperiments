#include "WeaponComponent.h"

#include "PlayerCharacter.h"

#include <Engine/GameEngine.h>
#include <Kismet/GameplayStatics.h>

#include <Camera/CameraComponent.h>

#include <EnhancedInputComponent.h>
#include <InputActionValue.h>

UWeaponComponent::UWeaponComponent() {

    PrimaryComponentTick.bCanEverTick = true;

}

void UWeaponComponent::BeginPlay() {

    Super::BeginPlay();

}
void UWeaponComponent::TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) {

    Super::TickComponent(deltaTime, tickType, thisTickFunction);

}

void UWeaponComponent::Attach(APlayerCharacter* character, UEnhancedInputComponent* inputComponent) {

    m_character = character;

    inputComponent->BindAction(fireAction, ETriggerEvent::Triggered, this, &UWeaponComponent::Fire);

}

void UWeaponComponent::Fire(const FInputActionValue& actionValue) {

    if (fireSound != nullptr)
        UGameplayStatics::PlaySoundAtLocation(this, fireSound, m_character->GetActorLocation());
    
    FCollisionQueryParams params = FCollisionQueryParams(FName("Weapon fire params"), true, m_character);
    params.bReturnPhysicalMaterial = false;
    params.bDebugQuery = true;

    UCameraComponent* camera = m_character->GetCameraComponent();

    FHitResult hit = FHitResult(ForceInit);
    FVector start = camera->GetComponentLocation();
    FVector end = start + (camera->GetForwardVector() * 10000.0f);
    if (!GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_GameTraceChannel1, params)) return;
    if (!hit.GetActor()->IsRootComponentMovable()) return;

    UPrimitiveComponent* hitComponent = Cast<UPrimitiveComponent>(hit.GetActor()->GetRootComponent());
    if (hitComponent == nullptr) return;

    hitComponent->AddImpulse(camera->GetForwardVector() * impactStrength * 1000.0f);

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Trace hit actor: %s"), *hit.GetActor()->GetName()));

}