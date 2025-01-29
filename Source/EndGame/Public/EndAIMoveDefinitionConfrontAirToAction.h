#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionConfrontToAction.h"
#include "EndAIMoveDefinitionConfrontAirToAction.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionConfrontAirToAction : public UEndAIMoveDefinitionConfrontToAction {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableMoveOnlyNavMesh;
    
    UEndAIMoveDefinitionConfrontAirToAction();

};

