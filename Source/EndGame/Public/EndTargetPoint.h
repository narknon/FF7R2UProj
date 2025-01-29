#pragma once
#include "CoreMinimal.h"
#include "AI/Navigation/NavRelevantInterface.h"
#include "Engine/TargetPoint.h"
#include "EndNaviMapDataProviderInterface.h"
#include "EndPackObjectInterface.h"
#include "EndTargetPointParameters.h"
#include "EndTargetPoint.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndTargetPoint : public ATargetPoint, public INavRelevantInterface, public IEndNaviMapDataProviderInterface, public IEndPackObjectInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndTargetPointParameters Parameters;
    
public:
    AEndTargetPoint(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

