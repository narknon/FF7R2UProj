#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndBattleDamageSourceCollisionDataSphere.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBattleDamageSourceCollisionDataSphere {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Center;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Radius;
    
    FEndBattleDamageSourceCollisionDataSphere();
};

