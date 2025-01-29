#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldActionTriggerComponentParamBase.h"
#include "EndFieldActionWallRunningTriggerParam.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndFieldActionWallRunningTriggerParam : public UEndFieldActionTriggerComponentParamBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bBlockBoxOutMove;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSetJumpDownPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 JumpDownPointPriority;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector JumpDownPoint;
    
    UEndFieldActionWallRunningTriggerParam();

};

