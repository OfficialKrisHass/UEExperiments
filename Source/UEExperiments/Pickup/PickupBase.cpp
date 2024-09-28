#include "PickupBase.h"

#include "../Weapon/WeaponManagerComponent.h"

#include "../Player/PlayerCharacter.h"

#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>

#include <Kismet/GameplayStatics.h>

APickupBase::APickupBase() {

	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(mesh);

	trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	trigger->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::BeginOverlap);
	trigger->SetupAttachment(mesh);

}

void APickupBase::BeginPlay() {

	Super::BeginPlay();

}

void APickupBase::BeginOverlap(UPrimitiveComponent* overllapedComp, AActor* actor, UPrimitiveComponent* otherComp, int32 otherIndex, bool fromSweep, const FHitResult& sweepResult) {

	TObjectPtr<APlayerCharacter> player = Cast<APlayerCharacter>(actor);
	if (player == nullptr) return;

	OnPickup(player);
	Destroy();

}