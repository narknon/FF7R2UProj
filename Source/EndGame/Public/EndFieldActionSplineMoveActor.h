#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EEndFieldSplineMoveType.h"
#include "EndFieldActionSaveActorBase.h"
#include "EndFieldActionSplineMoveActor.generated.h"

class UEndFieldActionTriggerComponent;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionSplineMoveActor : public AEndFieldActionSaveActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* TikableVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndFieldSplineMoveType MoveType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FTransform> CustomGuidEffectArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUpdateNaviLink;
    
public:
    AEndFieldActionSplineMoveActor(const FObjectInitializer& ObjectInitializer);

};

