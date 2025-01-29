#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndUserWidget.h"
#include "EndMemberChangeWindow.generated.h"

class UEndCanvasPanel;
class UEndMemberChangeDetail;
class UEndMemberChangeList;
class UEndPartySetSwitch;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMemberChangeWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberChangeList* List_1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberChangeList* List_2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_Arrow;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPartySetSwitch* PartySet_Switch;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberChangeDetail* Detail;
    
    UEndMemberChangeWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnReserveMemberSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnReserveMemberPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnReserveMemberMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnReserveMemberListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBattleMemberSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBattleMemberPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnBattleMemberMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBattleMemberListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
};

