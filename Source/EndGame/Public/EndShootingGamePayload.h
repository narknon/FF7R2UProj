#pragma once
#include "CoreMinimal.h"
#include "EEndShootingGameSectionType.h"
#include "EShootingAdaptiveEffectType.h"
#include "EShootingSEType.h"
#include "MovieSceneEndShootingGameParameters.h"
#include "EndShootingGamePayload.generated.h"

USTRUCT(BlueprintType)
struct FEndShootingGamePayload {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 Priority;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndShootingGameSectionType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetParamID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RouteActorName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 RouteIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SpeedRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bReverse;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SurvivalTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SendTriggerName;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EShootingSEType SEType;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EShootingAdaptiveEffectType FFBEffestType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEndShootingGameParameters Parameters;
    
    ENDGAME_API FEndShootingGamePayload();
};

