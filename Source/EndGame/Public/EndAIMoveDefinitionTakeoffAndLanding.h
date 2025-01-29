#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveDefinitionTakeoffAndLanding.h"
#include "EndAIMoveDefinition.h"
#include "EndAIMoveDefinitionMoveApproach.h"
#include "EndAIMoveDefinitionTakeoffAndLanding.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionTakeoffAndLanding : public UEndAIMoveDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIMoveDefinitionTakeoffAndLanding TakeoffAndLandingType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIMoveDefinitionMoveApproach MoveApproachLanding;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SequenceName;
    
    UEndAIMoveDefinitionTakeoffAndLanding();

};

