#pragma once
#include "CoreMinimal.h"
#include "EndMassiveEnvironmentComponent.h"
#include "EndMassiveEnvironmentFrameData.generated.h"

USTRUCT(BlueprintType)
struct FEndMassiveEnvironmentFrameData {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint64 FrameCounter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Timestamp;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndMassiveEnvironmentComponent> Components;
    
    ENDGAME_API FEndMassiveEnvironmentFrameData();
};

