#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndBodyControlRigHandEffectorHand.generated.h"

USTRUCT(BlueprintType)
struct FEndBodyControlRigHandEffectorHand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName HandBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EAxis::Type> HandBoneForwardAxis;
    
    ENDGAME_API FEndBodyControlRigHandEffectorHand();
};

