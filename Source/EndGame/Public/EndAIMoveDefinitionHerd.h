#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinition.h"
#include "EndAIMoveDefinitionMoveApproach.h"
#include "EndAIMoveDefinitionHerd.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionHerd : public UEndAIMoveDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ReplaceMoveDefinitionTags;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIMoveDefinitionMoveApproach MoveApproachIn;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIMoveDefinitionMoveApproach MoveApproachOut;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AreaInRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AreaOutRadius;
    
    UEndAIMoveDefinitionHerd();

};

