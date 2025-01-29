#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EEndAIMoveDefWarpToNearTheTargetType.h"
#include "EndEnvQueryTest_Enemy_WarpToNearTheTargetType.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_Enemy_WarpToNearTheTargetType : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIMoveDefWarpToNearTheTargetType WarpType;
    
    UEndEnvQueryTest_Enemy_WarpToNearTheTargetType();

};

