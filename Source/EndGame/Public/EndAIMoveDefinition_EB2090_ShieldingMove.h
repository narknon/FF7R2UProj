#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionMoveToMultiPointBase.h"
#include "EndAIMoveDefinition_EB2090_ShieldingMove.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinition_EB2090_ShieldingMove : public UEndAIMoveDefinitionMoveToMultiPointBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetPointNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bTargetDircLowPriority;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TargetDircLowPriorityAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSelfDircPriority;
    
    UEndAIMoveDefinition_EB2090_ShieldingMove();

};

