#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EEndAIRecognitionVolumeType.h"
#include "EndEnvQueryTest_DistanceToActiveRecognitionVolumeCenter.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_DistanceToActiveRecognitionVolumeCenter : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIRecognitionVolumeType VolumeType;
    
    UEndEnvQueryTest_DistanceToActiveRecognitionVolumeCenter();

};

