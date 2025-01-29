#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndChangeAppearanceBodyPrimitiveSettings.h"
#include "Templates/SubclassOf.h"
#include "EndChangeAppearanceSetting.generated.h"

class UAnimInstance;
class UEndAnimSet;
class UEndAssetPack;
class UEndBodyControlRig;
class UEndMaterialPack;
class USQEXSEADSound;
class USkeletalMesh;

USTRUCT(BlueprintType)
struct FEndChangeAppearanceSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USkeletalMesh* SkeletalMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndMaterialPack* MaterialPack;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UAnimInstance> AnimInstance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UEndAnimSet*> AnimSets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndBodyControlRig* BodyControlRig;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* SoundSE;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* SoundAutoSE;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAssetPack* EffectPack;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector RootCapsuleSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableChangeCapsuleSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndChangeAppearanceBodyPrimitiveSettings> CustomEndChangeAppearanceBodyPrimitiveSettings;
    
    ENDGAME_API FEndChangeAppearanceSetting();
};

