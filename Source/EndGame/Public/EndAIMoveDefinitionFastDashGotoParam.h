#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EEndAIMoveDefinitionFastDashGotoType.h"
#include "EndAIMoveDefinitionFastDashGotoParam.generated.h"

USTRUCT(BlueprintType)
struct FEndAIMoveDefinitionFastDashGotoParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIMoveDefinitionFastDashGotoType GotoType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LayoutItemName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector GotoOffset;
    
    ENDGAME_API FEndAIMoveDefinitionFastDashGotoParam();
};

