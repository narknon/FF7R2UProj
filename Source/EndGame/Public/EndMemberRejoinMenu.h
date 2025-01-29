#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMemberRejoinMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMemberRejoinMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndMemberRejoinMenu();

    UFUNCTION(BlueprintCallable)
    void OnReserveCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnRejoinCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCellCleanup(UWidget* ItemWidget);
    
};

