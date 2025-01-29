#pragma once
#include "CoreMinimal.h"
#include "eBodyParts.h"
#include "PartImpulseOverride.generated.h"

USTRUCT(BlueprintType)
struct FPartImpulseOverride {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<eBodyParts> Part;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Impulse;
    
    BODYDRIVERPLUGIN_API FPartImpulseOverride();
};

