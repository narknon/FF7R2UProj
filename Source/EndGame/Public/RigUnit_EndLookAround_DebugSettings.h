#pragma once
#include "CoreMinimal.h"
#include "Rigs/RigHierarchyDefines.h"
#include "EEndEmotionalGesture.h"
#include "RigUnit_EndLookAround_DebugSettings.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndLookAround_DebugSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnabled;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndEmotionalGesture EmotionalGesture;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigElementKey EffectorTargetItem;
    
    ENDGAME_API FRigUnit_EndLookAround_DebugSettings();
};

