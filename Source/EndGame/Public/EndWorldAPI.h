#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EEndStreamingSwitchType.h"
#include "EndWorldAPI.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndWorldAPI : public UObject {
    GENERATED_BODY()
public:
    UEndWorldAPI();

    UFUNCTION(BlueprintCallable)
    static void SwitchStreamingVolume(const FName VolumeLabel, const FName SwitchLabel, const EEndStreamingSwitchType SwitchType);
    
    UFUNCTION(BlueprintCallable)
    static void NeedSetupPlacement();
    
};

