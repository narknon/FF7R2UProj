#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SQEX_KineDriverEffectorExpr.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_KineDriverEffectorExpr {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FVector4> Inputs;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Code;
    
    KINEDRIVERRT_API FSQEX_KineDriverEffectorExpr();
};

