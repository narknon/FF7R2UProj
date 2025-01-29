#pragma once
#include "CoreMinimal.h"
#include "EndInteractorInterface.h"
#include "EndTargetPoint.h"
#include "EndInterestTargetPoint.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndInterestTargetPoint : public AEndTargetPoint, public IEndInteractorInterface {
    GENERATED_BODY()
public:
    AEndInterestTargetPoint(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

