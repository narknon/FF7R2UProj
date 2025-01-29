#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndCollisionDrawParams.generated.h"

USTRUCT(BlueprintType)
struct FEndCollisionDrawParams {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDrawShape;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDrawBBox;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FColor ShapeColor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FColor BBoxColor;
    
    ENDGAME_API FEndCollisionDrawParams();
};

