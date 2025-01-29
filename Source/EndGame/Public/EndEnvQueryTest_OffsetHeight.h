#pragma once
#include "CoreMinimal.h"
#include "DataProviders/AIDataProvider.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "Templates/SubclassOf.h"
#include "EndEnvQueryTest_OffsetHeight.generated.h"

class UEnvQueryContext;

UCLASS(Blueprintable)
class UEndEnvQueryTest_OffsetHeight : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEnvQueryContext> m_Context;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FAIDataProviderFloatValue m_Offset;
    
    UEndEnvQueryTest_OffsetHeight();

};

