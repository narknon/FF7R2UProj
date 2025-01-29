#pragma once
#include "CoreMinimal.h"
#include "EndBodyControlRigFootEffectorFoot.h"
#include "EndBodyControlRigFootEffectorSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndBodyControlRigFootEffectorSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBodyControlRigFootEffectorFoot> Foots;
    
    ENDGAME_API FEndBodyControlRigFootEffectorSetting();
};

