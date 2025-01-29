#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EMoogleShopNotifyType.h"
#include "EndAnimNotifyMoogleShopNotify.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyMoogleShopNotify : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EMoogleShopNotifyType NotifyEvent;
    
    UEndAnimNotifyMoogleShopNotify();

};

