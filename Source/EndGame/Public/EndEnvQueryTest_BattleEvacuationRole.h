#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "Templates/SubclassOf.h"
#include "EndEnvQueryTest_BattleEvacuationRole.generated.h"

class UEnvQueryContext;

UCLASS(Blueprintable)
class UEndEnvQueryTest_BattleEvacuationRole : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEnvQueryContext> TargetContext;
    
    UEndEnvQueryTest_BattleEvacuationRole();

};

