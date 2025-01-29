#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EEndControlBone.h"
#include "EEndControlBoneCondition.h"
#include "EEndControlBoneType.h"
#include "AnimNotify_EndBoneControlProperty.generated.h"

USTRUCT(BlueprintType)
struct FAnimNotify_EndBoneControlProperty {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndControlBone Bone;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndControlBoneType ControlType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Translation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRotator Rotation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndControlBoneCondition Condition;
    
    ENDGAME_API FAnimNotify_EndBoneControlProperty();
};

