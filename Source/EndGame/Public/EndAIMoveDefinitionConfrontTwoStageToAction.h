#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionConfrontToAction.h"
#include "EndAIMoveDefinitionConfrontTwoStageToActionInfo.h"
#include "Templates/SubclassOf.h"
#include "EndAIMoveDefinitionConfrontTwoStageToAction.generated.h"

class UEndAIActionDefinitionBase;

UCLASS(Blueprintable)
class UEndAIMoveDefinitionConfrontTwoStageToAction : public UEndAIMoveDefinitionConfrontToAction {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FirstMoveDurationTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FirstMoveDurationTimeWidth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIMoveDefinitionConfrontTwoStageToActionInfo> TwoStageMoveInfos;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIActionDefinitionBase> m_ActionDefinitionClass;
    
public:
    UEndAIMoveDefinitionConfrontTwoStageToAction();

};

