#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ESimpleInteractTarget.h"
#include "EndFieldSimpleInteractTargetTransSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldSimpleInteractTargetTransSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ESimpleInteractTarget MoveTargetType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform TargetWorldTransform;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform TargetTransformOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 ModifyMaskTransformParams;
    
    ENDGAME_API FEndFieldSimpleInteractTargetTransSetting();
};

