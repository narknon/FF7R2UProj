#pragma once
#include "CoreMinimal.h"
#include "SQEX_KineDriverSourceOther.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_KineDriverSourceOther {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Name;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString SubType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ParamNames;
    
    KINEDRIVERRT_API FSQEX_KineDriverSourceOther();
};

