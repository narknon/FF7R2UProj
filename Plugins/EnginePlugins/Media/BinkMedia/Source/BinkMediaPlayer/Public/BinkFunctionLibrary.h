#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BinkFunctionLibrary.generated.h"

UCLASS(Blueprintable)
class BINKMEDIAPLAYER_API UBinkFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UBinkFunctionLibrary();

    UFUNCTION(BlueprintCallable)
    static FTimespan BinkLoadingMovie_GetTime();
    
    UFUNCTION(BlueprintCallable)
    static FTimespan BinkLoadingMovie_GetDuration();
    
    UFUNCTION(BlueprintCallable)
    static void Bink_DrawOverlays();
    
};

