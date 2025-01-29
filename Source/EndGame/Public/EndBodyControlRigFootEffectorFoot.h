#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndBodyControlRigFootEffectorFoot.generated.h"

USTRUCT(BlueprintType)
struct FEndBodyControlRigFootEffectorFoot {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName FootBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EAxis::Type> FootBoneForwardAxis;
    
    ENDGAME_API FEndBodyControlRigFootEffectorFoot();
};

