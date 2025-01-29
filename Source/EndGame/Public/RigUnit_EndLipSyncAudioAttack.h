#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "RigUnit_EndLipSyncAudioAttack_Cache.h"
#include "RigUnit_EndLipSyncAudioAttack_Settings.h"
#include "RigUnit_EndLipSyncAudioAttack.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndLipSyncAudioAttack : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndLipSyncAudioAttack_Settings Settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndLipSyncAudioAttack_Cache Cache;
    
    ENDGAME_API FRigUnit_EndLipSyncAudioAttack();
};

