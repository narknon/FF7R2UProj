#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InputCoreTypes.h"
#include "EndSystemAPI.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndSystemAPI : public UObject {
    GENERATED_BODY()
public:
    UEndSystemAPI();

    UFUNCTION(BlueprintCallable)
    static void UpdateCharaPopLODDistance();
    
    UFUNCTION(BlueprintCallable)
    static bool IsTrialMode();
    
    UFUNCTION(BlueprintCallable)
    static bool IsPreviewEventMode();
    
    UFUNCTION(BlueprintCallable)
    static bool IsPlayableDemoMode();
    
    UFUNCTION(BlueprintCallable)
    static bool IsMediaDemoMode();
    
    UFUNCTION(BlueprintCallable)
    static bool IsMaster();
    
    UFUNCTION(BlueprintCallable)
    static bool IsInWestLocation_End2();
    
    UFUNCTION(BlueprintCallable)
    static bool IsInputKeyRepeat(FKey Key);
    
    UFUNCTION(BlueprintCallable)
    static bool IsInputKeyReleased(FKey Key);
    
    UFUNCTION(BlueprintCallable)
    static bool IsInputKeyPressed(FKey Key);
    
    UFUNCTION(BlueprintCallable)
    static bool IsInputKeyDown(FKey Key);
    
    UFUNCTION(BlueprintCallable)
    static bool IsInOceanLocation_End2();
    
    UFUNCTION(BlueprintCallable)
    static bool IsInNorthLocation_End2();
    
    UFUNCTION(BlueprintCallable)
    static bool IsInEastLocation_End2();
    
    UFUNCTION(BlueprintCallable)
    static bool IsExpansion3Mode();
    
    UFUNCTION(BlueprintCallable)
    static bool IsExpansion2Mode();
    
    UFUNCTION(BlueprintCallable)
    static bool IsEndGameMode();
    
    UFUNCTION(BlueprintCallable)
    static int32 GetCurrentLocationNumber_End2();
    
    UFUNCTION(BlueprintCallable)
    static FName GetCurrentLocation_End2();
    
    UFUNCTION(BlueprintCallable)
    static FString GetCommandLineOptionValue(const FString& Option);
    
    UFUNCTION(BlueprintCallable)
    static FString GetBuildTimeString();
    
    UFUNCTION(BlueprintCallable)
    static FString GetBuildRevisionString();
    
    UFUNCTION(BlueprintCallable)
    static void ForceGarbageCollection();
    
    UFUNCTION(BlueprintCallable)
    static void EnableWorldShift(bool bActive);
    
};

