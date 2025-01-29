#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyCondorChangeUnitID.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifyCondorChangeUnitID : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilityId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName UnitID;
    
    UEndAnimNotifyCondorChangeUnitID();

};

