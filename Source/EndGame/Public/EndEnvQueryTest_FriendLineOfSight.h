#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EndEnvQueryTest_FriendLineOfSight.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_FriendLineOfSight : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool ConsiderCheckOnNavmesh;
    
    UEndEnvQueryTest_FriendLineOfSight();

};

