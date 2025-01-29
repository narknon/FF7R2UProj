#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMainMenuWindow.h"
#include "EndMagicWindow.generated.h"

class UEndCanvasPanel;
class UEndCategoryTitle;
class UEndEquipInfo;
class UEndMagicSelectList;
class UEndMemberList;
class UEndRecoverList;
class UEndTextBlock;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMagicWindow : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCategoryTitle* CategoryTitle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberList* MemberList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfo* EquipInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMagicSelectList* Magic_SelectList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndRecoverList* Recover_List;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_TitleValue_Mp;
    
    UEndMagicWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnRecoverListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnRecoverListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnRecoverListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnRecoverListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMemberListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMagicListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMagicListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMagicListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMagicListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    bool OnMagicButtonUnhover();
    
    UFUNCTION(BlueprintCallable)
    bool OnMagicButtonHover();
    
};

