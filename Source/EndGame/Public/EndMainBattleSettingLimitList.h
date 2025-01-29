#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMainBattleSettingLimitList.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainBattleSettingLimitList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndMainBattleSettingLimitList();

private:
    UFUNCTION(BlueprintCallable)
    void OnEndBattleSettingLimitListLevel(UWidget* ItemWidget, int32 ItemIndex);
    
};

