#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMenuConstumeItemInfo.h"
#include "EndUserWidget.h"
#include "EndCostumeMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndCostumeMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndMenuConstumeItemInfo> ConstumeItemTable;
    
    UEndCostumeMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnScrollBoxMemberSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnScrollBoxMemberSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnScrollBoxMemberPressedItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnScrollBoxClothesSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnScrollBoxClothesSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnScrollBoxClothesPressedItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnScrollBoxClothesMeasureItem(int32 ItemIndex);
    
};

