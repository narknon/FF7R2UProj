#pragma once
#include "CoreMinimal.h"
#include "RigUnit_EndBodySpline_DebugSettings.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndBodySpline_DebugSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnabled;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDebugDraw;
    
    ENDGAME_API FRigUnit_EndBodySpline_DebugSettings();
};

