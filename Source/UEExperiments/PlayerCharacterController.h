#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

class UInputMappingContext;

UCLASS()
class UEEXPERIMENTS_API APlayerCharacterController : public APlayerController {

	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere) UInputMappingContext* mappingContext;

	virtual void BeginPlay() override;
	
};
