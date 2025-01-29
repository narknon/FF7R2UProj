#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "EndNaviMapDataProviderInterface.h"
#include "EndPackObjectInterface.h"
#include "EndTreasurePointParameters.h"
#include "EndTreasurePoint.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndTreasurePoint : public ATargetPoint, public IEndNaviMapDataProviderInterface, public IEndPackObjectInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndTreasurePointParameters Parameters;
    
public:
    AEndTreasurePoint(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

