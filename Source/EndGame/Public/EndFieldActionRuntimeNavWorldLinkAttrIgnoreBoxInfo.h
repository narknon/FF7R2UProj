#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldActionRuntimeNavWorldLinkAttrIgnoreBoxInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldActionRuntimeNavWorldLinkAttrIgnoreBoxInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform InvComponentTransform;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector BoxExtent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bActive;
    
    ENDGAME_API FEndFieldActionRuntimeNavWorldLinkAttrIgnoreBoxInfo();
};

