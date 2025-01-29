#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EEndAnimRopeConstraint.h"
#include "AnimNotify_EndRopeIgnoreConstraint.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UAnimNotify_EndRopeIgnoreConstraint : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimRopeConstraint Constraint;
    
    UAnimNotify_EndRopeIgnoreConstraint();

};

