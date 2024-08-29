#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PlayerCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCharacter, Log, All);

class UCameraComponent;

class UInputAction;
struct FInputActionValue;

UCLASS()
class UEEXPERIMENTS_API APlayerCharacter : public ACharacter {

	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void Tick(float deltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere) UCameraComponent* camera;

	UPROPERTY(EditAnywhere) UInputAction* moveAction;
	UPROPERTY(EditAnywhere) UInputAction* lookAction;

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& actionValue);
	void Look(const FInputActionValue& actionValue);
	
};