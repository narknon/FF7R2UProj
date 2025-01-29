#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "EndTinyBroncoDolphinActionDefinition.h"
#include "EndTinyBroncoDolphinActionLotteryListPerSpeed.h"
#include "EndTinyBroncoDolphinAreaSplineActor.generated.h"

class UEndTinyBroncoDolphinAreaSplineComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndTinyBroncoDolphinAreaSplineActor : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndTinyBroncoDolphinActionDefinition> ActionDefinitionList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndTinyBroncoDolphinActionLotteryListPerSpeed> LotteryList;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval LotteryInterval;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float NextLotterySubtractTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CoolDownTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Priority;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 MaxEventNum;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTinyBroncoDolphinAreaSplineComponent* SplineComponent;
    
public:
    AEndTinyBroncoDolphinAreaSplineActor(const FObjectInitializer& ObjectInitializer);

};

