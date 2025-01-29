#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinition.h"
#include "EndAIMoveDefinitionMoveApproach.h"
#include "EndAIMoveDefinitionMoveToNearTheGroupMember.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionMoveToNearTheGroupMember : public UEndAIMoveDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName GroupId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName IndividualTag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIMoveDefinitionMoveApproach MoveApproachAccess;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PointRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCheckAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CheckAngle;
    
    UEndAIMoveDefinitionMoveToNearTheGroupMember();

};

