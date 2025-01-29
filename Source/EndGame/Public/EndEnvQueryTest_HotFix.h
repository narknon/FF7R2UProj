#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EEndQueryTestHotFixType.h"
#include "EndEnvQueryTest_HotFix.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_HotFix : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndQueryTestHotFixType HotFixType;
    
    UEndEnvQueryTest_HotFix();

};

