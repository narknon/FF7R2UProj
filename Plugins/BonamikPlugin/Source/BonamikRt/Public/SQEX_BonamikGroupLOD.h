#pragma once
#include "CoreMinimal.h"
#include "SQEX_BonamikGroupLOD.generated.h"

USTRUCT(BlueprintType)
struct BONAMIKRT_API FSQEX_BonamikGroupLOD {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> Groups;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PreRollTime;
    
    FSQEX_BonamikGroupLOD();
};

