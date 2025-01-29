#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndAnimNotifyBattleDamageOwnerFilterType.h"
#include "EEndBattleDamageSourcePositionBaseType.h"
#include "EndAnimNotifyBattleDamageDisplay.generated.h"

UCLASS(Blueprintable, CollapseCategories, Deprecated, NotPlaceable)
class ENDGAME_API UDEPRECATED_EndAnimNotifyBattleDamageDisplay : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString DamageSourceID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBattleDamageSourcePositionBaseType CreatePositionBase;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CreatePositionName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ReplaceOwnerCharaName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimNotifyBattleDamageOwnerFilterType OwnerFilterType;
    
    UDEPRECATED_EndAnimNotifyBattleDamageDisplay();

};

