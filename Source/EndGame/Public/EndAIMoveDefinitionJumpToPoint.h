#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyPointSelectType.h"
#include "EndAIMoveDefinitionJumpBase.h"
#include "EndAIMoveDefinitionJumpToPoint.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionJumpToPoint : public UEndAIMoveDefinitionJumpBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetPointNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIEnemyPointSelectType PointSelectType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bTurnToJump;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bWall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bForceJump;
    
    UEndAIMoveDefinitionJumpToPoint();

};

