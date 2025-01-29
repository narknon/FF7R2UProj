#pragma once
#include "CoreMinimal.h"
#include "CommonAnimTypes.h"
#include "Engine/DataAsset.h"
#include "EndBodyControlRigFootEffectorSetting.h"
#include "EndBodyControlRigHandEffectorSetting.h"
#include "EndBoneBlendRateGroup.h"
#include "EndCharacterMovementExpressionSetting.h"
#include "EndBodyControlRig.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndBodyControlRig : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CenterBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName HeadBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FAxis HeadBoneForwardAxis;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LookAtTargetBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> FullBodyBoneBlendTargets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndBoneBlendRateGroup> BoneBlendRateGroups;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AIWalkRotationRateScale;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AIRunRotationRateScale;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AIDashRotationRateScale;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBodyControlRigFootEffectorSetting FootEffector;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBodyControlRigHandEffectorSetting HandEffector;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCharacterMovementExpressionSetting MovementExpressionSetting;
    
    UEndBodyControlRig();

};

