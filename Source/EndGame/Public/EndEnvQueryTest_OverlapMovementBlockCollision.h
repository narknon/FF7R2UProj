#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EndEnvQueryTest_OverlapMovementBlockCollision.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_OverlapMovementBlockCollision : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OffsetZ;
    
    UEndEnvQueryTest_OverlapMovementBlockCollision();

};

