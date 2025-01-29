#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EEnvQueryTest_DamageSource_AffectedType.h"
#include "EndEnvQueryTest_DamageSource.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_DamageSource : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEnvQueryTest_DamageSource_AffectedType Type;
    
    UEndEnvQueryTest_DamageSource();

};

