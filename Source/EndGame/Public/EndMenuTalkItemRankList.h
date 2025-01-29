#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMenuTalkItemRankList.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMenuTalkItemRankList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndMenuTalkItemRankList();

private:
    UFUNCTION(BlueprintCallable)
    void OnRankListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnList3SetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnList2SetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnList1SetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnList0SetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnList01SetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

