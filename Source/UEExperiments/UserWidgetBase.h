#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetBase.generated.h"

UCLASS(Abstract)
class UEEXPERIMENTS_API UUserWidgetBase : public UUserWidget {

	GENERATED_BODY()

public:
#ifdef WITH_EDITOR
	inline virtual const FText GetPaletteCategory() override { return NSLOCTEXT("UMG", "CustomPaletteCategory", "Kris Hass"); }
#endif
	
};
