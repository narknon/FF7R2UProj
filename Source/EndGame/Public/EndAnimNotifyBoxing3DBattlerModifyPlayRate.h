#pragma once
#include "CoreMinimal.h"
#include "AnimNotify_EndModifyPlayRate.h"
#include "EndAnimNotifyBoxing3DBattlerModifyPlayRate.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class ENDGAME_API UEndAnimNotifyBoxing3DBattlerModifyPlayRate : public UAnimNotify_EndModifyPlayRate {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ComboSpeedScaleFactor;
    
public:
    UEndAnimNotifyBoxing3DBattlerModifyPlayRate();

};

