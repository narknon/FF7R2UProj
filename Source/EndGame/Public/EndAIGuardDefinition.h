#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyGuardExecSate.h"
#include "EndAIActionDefinition.h"
#include "EndAIGuardDefinition.generated.h"

UCLASS(Blueprintable)
class UEndAIGuardDefinition : public UEndAIActionDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName DefenseID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float GuardTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float GuardTimeMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAIEnemyGuardExecSate> ExecSates;
    
    UEndAIGuardDefinition();

};

