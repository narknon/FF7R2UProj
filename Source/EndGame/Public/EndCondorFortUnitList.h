#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCondorFortUnitList.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndCondorFortUnitList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndCondorFortUnitList();

protected:
    UFUNCTION(BlueprintCallable)
    void OnSetup_List_UniqueUnit(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSetup_List_Switch(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSetup_List_PlayerUnit(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSetup_List_EnemyUnit(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSetup_List_BossUnit(UWidget* ItemWidget, int32 ItemIndex);
    
};

