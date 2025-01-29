#pragma once
#include "CoreMinimal.h"
#include "RigUnit_EndHandControl_DebugHandSettings.h"
#include "RigUnit_EndHandControl_DebugSettings.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndHandControl_DebugSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnabled;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDrawTrace;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableInterp;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FRigUnit_EndHandControl_DebugHandSettings> Hands;
    
    ENDGAME_API FRigUnit_EndHandControl_DebugSettings();
};

