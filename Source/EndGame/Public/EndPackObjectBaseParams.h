#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndPackObjectBaseParams.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndPackObjectBaseParams {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 TypeHash;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 IndexToAppendParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform Transform;
    
    FEndPackObjectBaseParams();
};

