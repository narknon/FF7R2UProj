#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMainMenuWindow.h"
#include "EndBattleReportMenu.generated.h"

class UEndSortWindow;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndBattleReportMenu : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSortWindow* SortList;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FString, FSoftObjectPath> _ReportImages;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FString, FSoftObjectPath> _ReportBgImages;
    
public:
    UEndBattleReportMenu();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SetReportImage(const FSoftObjectPath& Path);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SetReportBgImage(const FSoftObjectPath& Path);
    
private:
    UFUNCTION(BlueprintCallable)
    void OnSortListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnReportMenuSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnReportMenuSelectedIndexChanged(int32 CellIndex);
    
};

