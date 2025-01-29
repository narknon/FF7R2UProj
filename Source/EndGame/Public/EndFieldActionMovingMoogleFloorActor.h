#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionCommonActorBase.h"
#include "EndFieldActionMovingMoogleFloorActor.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldActionMovingMoogleFloorActor : public AEndFieldActionCommonActorBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SpeedScale;
    
    AEndFieldActionMovingMoogleFloorActor(const FObjectInitializer& ObjectInitializer);

};

