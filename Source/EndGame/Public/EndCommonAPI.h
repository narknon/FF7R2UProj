#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndCommonAPI.generated.h"

UCLASS(Blueprintable)
class UEndCommonAPI : public UObject {
    GENERATED_BODY()
public:
    UEndCommonAPI();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 RandomIntegerInRange(int32 Min, int32 Max);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float RandomFloatInRange(float Min, float Max);
    
};

