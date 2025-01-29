#pragma once
#include "CoreMinimal.h"
#include "EndRestrictedAreaWallCollisionBuildParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndRestrictedAreaWallCollisionBuildParameter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RightOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WallThickness;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float UpperHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LowerHeight;
    
    ENDGAME_API FEndRestrictedAreaWallCollisionBuildParameter();
};

