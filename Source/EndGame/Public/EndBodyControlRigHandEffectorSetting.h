#pragma once
#include "CoreMinimal.h"
#include "EndBodyControlRigHandEffectorHand.h"
#include "EndBodyControlRigHandEffectorSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndBodyControlRigHandEffectorSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBodyControlRigHandEffectorHand> Hands;
    
    ENDGAME_API FEndBodyControlRigHandEffectorSetting();
};

