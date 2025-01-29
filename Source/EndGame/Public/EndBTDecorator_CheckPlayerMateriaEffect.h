#pragma once
#include "CoreMinimal.h"
#include "EAIPCMateriaEffect.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckPlayerMateriaEffect.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckPlayerMateriaEffect : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAIPCMateriaEffect MateriaEffectType;
    
    UEndBTDecorator_CheckPlayerMateriaEffect();

};

