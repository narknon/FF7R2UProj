#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyBoxing3DBattlerLimitBreakKO.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyBoxing3DBattlerLimitBreakKO : public UAnimNotify {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform HitTransform;
    
public:
    UEndAnimNotifyBoxing3DBattlerLimitBreakKO();

};

