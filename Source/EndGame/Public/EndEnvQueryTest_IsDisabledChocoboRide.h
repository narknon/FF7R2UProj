#pragma once
#include "CoreMinimal.h"
#include "DataProviders/AIDataProvider.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EndEnvQueryTest_IsDisabledChocoboRide.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_IsDisabledChocoboRide : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FAIDataProviderBoolValue m_bLeaderChocoboOnly;
    
    UEndEnvQueryTest_IsDisabledChocoboRide();

};

