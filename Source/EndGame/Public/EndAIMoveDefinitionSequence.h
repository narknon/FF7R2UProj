#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinition.h"
#include "EndAIMoveDefinitionSequenceInfo.h"
#include "Templates/SubclassOf.h"
#include "EndAIMoveDefinitionSequence.generated.h"

class UEndAIActionDefinitionBase;

UCLASS(Blueprintable)
class UEndAIMoveDefinitionSequence : public UEndAIMoveDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIMoveDefinitionSequenceInfo> MoveDefinitionSequenceInfos;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SuspendExtraConditionTag;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIActionDefinitionBase> m_ActionDefinitionClass;
    
public:
    UEndAIMoveDefinitionSequence();

};

