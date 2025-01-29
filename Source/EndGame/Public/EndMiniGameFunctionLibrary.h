#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EndMiniGameFunctionLibrary.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndMiniGameFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UEndMiniGameFunctionLibrary();

    UFUNCTION(BlueprintCallable)
    static void ResetGambitGeneralCondition();
    
    UFUNCTION(BlueprintCallable)
    static bool PlayLifeGaugeAnimation(int32 idx, bool bForward);
    
    UFUNCTION(BlueprintCallable)
    static int32 GetLifestreamValue();
    
    UFUNCTION(BlueprintCallable)
    static float GetLifeGaugeRate();
    
    UFUNCTION(BlueprintCallable)
    static void AddGambitMinigamePhase();
    
};

