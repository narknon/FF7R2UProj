#pragma once
#include "CoreMinimal.h"
#include "Sound/SlateSound.h"
#include "EndUserWidget.h"
#include "Templates/SubclassOf.h"
#include "EndStartMenu.generated.h"

class UEndMainMenu;
class UEndMainOptionsMenu;
class UUserWidget;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndStartMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndUserWidget> LoadMenuWidgetClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndUserWidget> OptionsMenuWidgetClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateSound NewGameSound;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ButtonAnimationStartTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ButtonAnimationDelay;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndUserWidget> TrialPlayModeDetailWidgetClass;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndUserWidget* Throbber;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndUserWidget* CachedLoadMenu;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndMainMenu* MainMenu;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndMainOptionsMenu* OptionsMenu;
    
public:
    UEndStartMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnSaveDataSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSaveDataSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSaveDataPressedItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSaveDataClicked(UUserWidget* Cell);
    
    UFUNCTION(BlueprintCallable)
    void OnSaveDataCancelled();
    
    UFUNCTION(BlueprintCallable)
    void OnQuitGame();
    
    UFUNCTION(BlueprintCallable)
    void OnOptions();
    
    UFUNCTION(BlueprintCallable)
    void OnNewGame();
    
    UFUNCTION(BlueprintCallable)
    void OnLoadLatest();
    
    UFUNCTION(BlueprintCallable)
    void OnLoadGame();
    
    UFUNCTION(BlueprintCallable)
    void OnListMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListMenuSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListMenuPressedItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCharaFaceSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

