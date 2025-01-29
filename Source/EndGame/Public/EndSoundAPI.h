#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EEndSoundLayer.h"
#include "EndSoundAPI.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndSoundAPI : public UObject {
    GENERATED_BODY()
public:
    UEndSoundAPI();

    UFUNCTION(BlueprintCallable)
    static void SetExternalParameter(FName ParameterName, float Value);
    
    UFUNCTION(BlueprintCallable)
    static void SendAudioVolumeEvent(FName AudioVolumeEventID, FName ActorName);
    
    UFUNCTION(BlueprintCallable)
    static void CallEvent(EEndSoundLayer TargetLayer);
    
};

