#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BikeCutterStormAbilitySetting.generated.h"

USTRUCT(BlueprintType)
struct FBikeCutterStormAbilitySetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LoopTime;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FFloatInterval> AttackTimings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BeginMotion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EndMotion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AddMotion_Attack;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MoveRange;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 FirstMoveDirectionSign;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MoveSpeed;
    
    ENDGAME_API FBikeCutterStormAbilitySetting();
};

