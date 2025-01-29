#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndUserWidget.h"
#include "EndCategoryTitleMember.generated.h"

class UEndIconMember;
class UEndMenuCategoryChangeBtn;
class UEndTextBlock;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndCategoryTitleMember : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_MainTitle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMenuCategoryChangeBtn* CategorySwitch;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndIconMember* Icon_Member;
    
    UEndCategoryTitleMember();

private:
    UFUNCTION(BlueprintCallable)
    void OnSelectItemSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnSelectItemMeasureItem(int32 CellIndex);
    
};

