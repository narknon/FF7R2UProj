#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "Styling/SlateBrush.h"
#include "EndUserWidget.h"
#include "EndFieldCommandMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndFieldCommandMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSlateBrush> _CommandGaugeColors;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor _ReserveMemberTextColor;
    
    UEndFieldCommandMenu();

    UFUNCTION(BlueprintCallable)
    void OnPressedItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandMemberSelecterIconSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnCommandMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandHelpAbilityIcon(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
};

