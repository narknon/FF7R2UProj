#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EEndAIRecognitionVolumeType.h"
#include "EndEnvQueryTest_InRecognitionVolume.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_InRecognitionVolume : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIRecognitionVolumeType VolumeType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 GroupId;
    
    UEndEnvQueryTest_InRecognitionVolume();

};

