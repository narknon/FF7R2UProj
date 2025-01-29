#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveDefinitionStepDirction.h"
#include "EndAIAnimDefinition.h"
#include "EndAIAnimDefinitionAvoid.generated.h"

UCLASS(Blueprintable)
class UEndAIAnimDefinitionAvoid : public UEndAIAnimDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIMoveDefinitionStepDirction DirctionType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MoveDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bTraceWall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCheckBattleArea;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDrawDebug;
    
    UEndAIAnimDefinitionAvoid();

};

