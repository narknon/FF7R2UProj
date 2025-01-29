#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Object.h"
#include "EndBattleDevelop.generated.h"

UCLASS(Blueprintable)
class UEndBattleDevelop : public UObject {
    GENERATED_BODY()
public:
    UEndBattleDevelop();

    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void PrintString(UObject* WorldContextObject, const FString& inString, bool bPrintToScreen, bool bPrintToLog, FLinearColor TextColor, float Duration);
    
};

