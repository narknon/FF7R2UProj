#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SQEX_KineDriver_AnimNotify_Param.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class KBDRT_API USQEX_KineDriver_AnimNotify_Param : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, float> Params;
    
    USQEX_KineDriver_AnimNotify_Param();

};

