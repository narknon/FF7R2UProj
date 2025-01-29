#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ESQEX_Bonamik_FastMotionHandling.h"
#include "ESQEX_Bonamik_JointLinkSimulationMode.h"
#include "SQEX_BonamikFpsCorrectionDesc.h"
#include "SQEX_BonamikSceneManagerDesc.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_BonamikSceneManagerDesc {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_IsEnable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_IsEnableLocalForce;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_EnableGroundCollision;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool mAccurateGroundCollision;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool mPerJointWindSample;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool mUseAuthoredTimestep;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool mUseTimestepSmoother;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool mIsCollisionResampleCapsule;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool mIsCollisionResponsiveLateral;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool mCollisionBVH;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 mFastMotionHandling;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 mReferenceFrameUpdateMode;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 mPreStep;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_SubStep;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 mNetworkIter;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 mLateralIter;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 mCollisionIter;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 mCollisionCacheMaxLife;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 mCollisionCacheSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mCollisionResampleCapsuleStep;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mCollisionCachableRange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mCollisionCacheInvalidateThreshold;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mSpeedClamp;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mAccelerationClamp;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float mAnimBlend;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_Dt;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector m_Gravity;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_RefUpVec;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSQEX_BonamikFpsCorrectionDesc> mFpsCorrection;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_IsUseGPU;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_TotalGroup;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FString m_GroupName[48];
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_IsEnableLSS;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_LSScoeff_tran;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_LSScoeff_rot;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString m_RootName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector m_WindForce;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector m_DirRange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector m_ForceRange;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_TotalLinkBatches;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_TotalLinksInBatch[15];
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_TotalConeBatches;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_TotalConesInBatch[15];
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_TotalCollisionBatches;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_TotalCollisionsInBatch[15];
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_TotalSelfCollisionBatches;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_TotalSelfCollisionsInBatch[15];
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESQEX_Bonamik_JointLinkSimulationMode> m_JointLinkSimulationMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESQEX_Bonamik_FastMotionHandling> m_FastMotionHandlingMode;
    
    BONAMIKRT_API FSQEX_BonamikSceneManagerDesc();
};

