#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "ENavAgentPropertyCategory.h"
#include "EEndQueryFilterType.h"
#include "Templates/SubclassOf.h"
#include "EndEnvQueryTest_ExistsNavMesh.generated.h"

class UEnvQueryContext;

UCLASS(Blueprintable)
class UEndEnvQueryTest_ExistsNavMesh : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndQueryFilterType QueryFilterType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bApplyDynamicFilter;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bPathFindToContext;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEnvQueryContext> PathFindTargetContext;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ENavAgentPropertyCategory NavAgentPropertyCategory;
    
    UEndEnvQueryTest_ExistsNavMesh();

};

