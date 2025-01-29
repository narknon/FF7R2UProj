#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EndNaviMapStateRenderTargetLibrary.generated.h"

class UEndNaviMapStateRenderTarget;
class UObject;

UCLASS(Blueprintable)
class UEndNaviMapStateRenderTargetLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UEndNaviMapStateRenderTargetLibrary();

    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static UEndNaviMapStateRenderTarget* CreateStateRenderTarget(UObject* WorldContextObject, int32 Width, int32 Height);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static UEndNaviMapStateRenderTarget* CreateStateGradationRenderTarget(UObject* WorldContextObject);
    
};

