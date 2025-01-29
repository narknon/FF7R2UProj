#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SQEX_AnimNotify_Bonamik_Ensemble.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class KBDRT_API USQEX_AnimNotify_Bonamik_Ensemble : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EnsembleName;
    
    USQEX_AnimNotify_Bonamik_Ensemble();

};

