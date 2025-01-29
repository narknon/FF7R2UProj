#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EForceParkourCheckType.h"
#include "EForceParkourJumpType.h"
#include "EForceParkourSetType.h"
#include "EndFieldActionRuntimeNavWorldLinkAttrIgnoreBoxInfo.h"
#include "EndFieldForceParkourCustomGuidEffectInfo.h"
#include "EndFieldForceParkourSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldForceParkourSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EForceParkourSetType SetType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EForceParkourJumpType JumpType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EForceParkourCheckType CheckType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FVector> Lines;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> LineNums;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> AttachParkourNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldForceParkourCustomGuidEffectInfo> GuidEffectInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldActionRuntimeNavWorldLinkAttrIgnoreBoxInfo> IgnoreBoxInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AddtiveJumpHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLandFaildToSafeTeleport;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector CsParkourBoundBoxMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector CsParkourBoundBoxMax;
    
    ENDGAME_API FEndFieldForceParkourSetting();
};

