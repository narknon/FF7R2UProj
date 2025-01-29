#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "EndChadleyPointParameters.h"
#include "EndNaviMapDataProviderInterface.h"
#include "EndPackObjectInterface.h"
#include "EndChadleyPoint.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndChadleyPoint : public ATargetPoint, public IEndNaviMapDataProviderInterface, public IEndPackObjectInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndChadleyPointParameters Parameters;
    
    AEndChadleyPoint(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

