#pragma once

#include "CoreMinimal.h"
#include "UserWidgetBase.h"
#include "AmmoInfo.generated.h"

class UTextBlock;

class AMainHUD;

UCLASS(Abstract)
class UEEXPERIMENTS_API UAmmoInfo : public UUserWidgetBase {

	GENERATED_BODY()

	friend AMainHUD;

public:

#if WITH_EDITOR
	virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	TObjectPtr<UTextBlock> inMagText = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	TObjectPtr<UTextBlock> magsText = nullptr;

	UFUNCTION()
	void OnAmmoUpdated(uint8 oldAmmo, uint8 newAmmo, uint8 oldMags, uint8 newMags);

	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(EditAnywhere, meta = (ClampMax = 99, UIMax = 99)) uint8 inMag = 0;
	UPROPERTY(EditAnywhere) uint8 mags = 0;

	void UpdateWidget();
	
};
