#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionJumpBase.h"
#include "EndAIMoveDefinitionMoveApproach.h"
#include "EndAIMoveDefinitionJumpToCeiling.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionJumpToCeiling : public UEndAIMoveDefinitionJumpBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIMoveDefinitionMoveApproach MoveApproachInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetPointNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TargetPointGoalRadius;
    
    UEndAIMoveDefinitionJumpToCeiling();

};

