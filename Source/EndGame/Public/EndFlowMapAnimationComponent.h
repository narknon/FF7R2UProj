#pragma once
#include "CoreMinimal.h"
#include "EndFlowMapAnimationComponentBase.h"
#include "EndFlowMapAnimationSettings.h"
#include "EndFlowMapAnimationComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndFlowMapAnimationComponent : public UEndFlowMapAnimationComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFlowMapAnimationSettings FlowMapAnimationSettings;
    
    UEndFlowMapAnimationComponent(const FObjectInitializer& ObjectInitializer);

};

