#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "HSFLipMapShape.h"
#include "HSFLipSyncInput.h"
#include "AnimNode_HSFLipSync.generated.h"

class UHSFLipMap;

USTRUCT(BlueprintType)
struct HSFLIPSYNCRUNTIME_API FAnimNode_HSFLipSync : public FAnimNode_Base {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, UHSFLipMap*> LipMaps;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FHSFLipSyncInput Input;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FHSFLipMapShape DummyShape;
    
    FAnimNode_HSFLipSync();

    // Override required functions
    virtual void Initialize_AnyThread(const FAnimationInitializeContext &Context) override;
    virtual void Update_AnyThread(const FAnimationUpdateContext &Context) override;
    virtual void Evaluate_AnyThread(FPoseContext &Output) override;
};

