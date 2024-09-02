#include "WeaponComponent.h"

#include "PlayerCharacter.h"

#include <Engine/GameEngine.h>
#include <Kismet/GameplayStatics.h>

#include <Camera/CameraComponent.h>

UWeaponComponent::UWeaponComponent() {

    PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponComponent::BeginPlay() {

    Super::BeginPlay();

}

void UWeaponComponent::Fire(APlayerCharacter* character) {

    if (ammo == 0) return;
    ammo--;

    if (fireSound != nullptr)
        UGameplayStatics::PlaySoundAtLocation(this, fireSound, character->GetActorLocation());
    
    FCollisionQueryParams params = FCollisionQueryParams(FName("Weapon fire params"), true, character);
    params.bReturnPhysicalMaterial = false;
    params.bDebugQuery = true;

    UCameraComponent* camera = character->GetCameraComponent();

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
void UWeaponComponent::Reload(APlayerCharacter* character) {

    if (mags == 0) return;

    ammo = magSize;
    mags--;

}