#pragma once
#include "CoreMinimal.h"
#include "EFriendBattleCautionType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckBattleCautionType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckBattleCautionType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EFriendBattleCautionType Type;
    
    UEndBTDecorator_CheckBattleCautionType();

};

