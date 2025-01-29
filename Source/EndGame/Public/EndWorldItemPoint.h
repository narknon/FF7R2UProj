#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "EndNaviMapDataProviderInterface.h"
#include "EndPackObjectInterface.h"
#include "EndWorldItemParameters.h"
#include "EndWorldItemPoint.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndWorldItemPoint : public ATargetPoint, public IEndNaviMapDataProviderInterface, public IEndPackObjectInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWorldItemParameters Parameters;
    
public:
    AEndWorldItemPoint(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

