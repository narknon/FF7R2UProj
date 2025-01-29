#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveDefWarpToNearTheTargetType.h"
#include "EndAIMoveDefinitionWarpBase.h"
#include "EndAIMoveDefinitionWarpToNearTheTarget.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionWarpToNearTheTarget : public UEndAIMoveDefinitionWarpBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIMoveDefWarpToNearTheTargetType SelectPointType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WarpLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WarpAngle;
    
    UEndAIMoveDefinitionWarpToNearTheTarget();

};

