#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EEndAIFollowPosition.h"
#include "EndEnvQueryTest_Follow_CheckPositionType.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_Follow_CheckPositionType : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIFollowPosition m_PositionType;
    
    UEndEnvQueryTest_Follow_CheckPositionType();

};

