#include "AmmoInfo.h"

#include <Components/TextBlock.h>

void UAmmoInfo::NativeOnInitialized() {

	Super::NativeOnInitialized();
    
	UpdateWidget();

}

void UAmmoInfo::OnAmmoUpdated(uint8 oldAmmo, uint8 newAmmo, uint8 oldMags, uint8 newMags) {

    if (newAmmo == inMag && newMags == mags) return;

    inMag = newAmmo;
    mags = newMags;

    UpdateWidget();

}

void UAmmoInfo::UpdateWidget() {

    if (inMagText == nullptr || magsText == nullptr) return;

    inMagText->SetText(FText::FromString(FString::Printf(TEXT("%02d"), inMag)));
    magsText->SetText(FText::FromString(FString::FromInt(mags)));

}

#ifdef WITH_EDITOR
void UAmmoInfo::OnDesignerChanged(const FDesignerChangedEventArgs& args) {

    Super::OnDesignerChanged(args);

    UpdateWidget();

}
void UAmmoInfo::PostEditChangeProperty(FPropertyChangedEvent& event) {

    Super::PostEditChangeProperty(event);

    const FString propName = (event.Property != nullptr) ? event.Property->GetFName().ToString() : TEXT("");
    //if (propName != TEXT("InMag") || propName != TEXT("Mags")) return;

    UpdateWidget();

}
#endif