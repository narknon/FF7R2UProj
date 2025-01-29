#pragma once
#include "CoreMinimal.h"
#include "EndTriggerBox.h"
#include "ToroccoYuffieTriggerBox.generated.h"

class AEndActionYuffieBox;

UCLASS(Blueprintable)
class ENDGAME_API AToroccoYuffieTriggerBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndActionYuffieBox* TargetBox;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TotalTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Tolerance_MinimumPassTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinimumPassTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaximumPassTime;
    
public:
    AToroccoYuffieTriggerBox(const FObjectInitializer& ObjectInitializer);

};

