#pragma once

#include "CoreMinimal.h"
#include "UserWidgetBase.h"
#include "MainLayout.generated.h"

class UAmmoInfo;

UCLASS(Abstract)
class UEEXPERIMENTS_API UMainLayout : public UUserWidgetBase {

	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	TObjectPtr<UAmmoInfo> ammoInfo = nullptr;
	
};
