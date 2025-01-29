#pragma once
#include "CoreMinimal.h"
#include "EEndStreamingVolumeTargetType.h"
#include "EndStreamingSwitchSet.generated.h"

class UWorld;

USTRUCT(BlueprintType)
struct FEndStreamingSwitchSet {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SwitchLabel;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSoftObjectPtr<UWorld>> StreamingLevels;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndStreamingVolumeTargetType StreamingTarget;
    
    ENDGAME_API FEndStreamingSwitchSet();
};

