#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_EndMarker.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UAnimNotify_EndMarker : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MarkerName;
    
    UAnimNotify_EndMarker();

};

