#pragma once
#include "CoreMinimal.h"
#include "EndWheelAnimSetup.generated.h"

USTRUCT(BlueprintType)
struct FEndWheelAnimSetup {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RollBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SusBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SteerAngleRate;
    
    ENDGAME_API FEndWheelAnimSetup();
};

