#pragma once
#include "CoreMinimal.h"
#include "EndTriggerBox.h"
#include "EndChocoboRaceCourseOutTriggerBox.generated.h"

class AEndTargetPoint;

UCLASS(Blueprintable)
class AEndChocoboRaceCourseOutTriggerBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<AEndTargetPoint> ReturnPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ReturnPointName;
    
public:
    AEndChocoboRaceCourseOutTriggerBox(const FObjectInitializer& ObjectInitializer);

};

