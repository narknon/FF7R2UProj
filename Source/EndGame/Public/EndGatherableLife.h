#pragma once
#include "CoreMinimal.h"
#include "EndGatherableLife.generated.h"

class AEndSelectTargetPoint;
class UObject;

USTRUCT(BlueprintType)
struct ENDGAME_API FEndGatherableLife {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_LifeAmount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UObject* m_VFXAssetUserData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_GatheredEvent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<AEndSelectTargetPoint> m_ShareSelectItem;
    
    FEndGatherableLife();
};

