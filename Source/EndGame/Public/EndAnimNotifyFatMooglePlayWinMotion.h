#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyFatMooglePlayWinMotion.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifyFatMooglePlayWinMotion : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartTime;
    
    UEndAnimNotifyFatMooglePlayWinMotion();

};

