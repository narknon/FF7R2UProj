#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndHandType.h"
#include "AnimNotify_EndReinsConstraint.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndReinsConstraint : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndHandType HandType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAttach;
    
    UAnimNotify_EndReinsConstraint();

};

