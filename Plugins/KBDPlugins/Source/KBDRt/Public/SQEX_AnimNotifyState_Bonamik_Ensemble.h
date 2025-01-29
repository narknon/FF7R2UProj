#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SQEX_AnimNotifyState_Bonamik_Ensemble.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class KBDRT_API USQEX_AnimNotifyState_Bonamik_Ensemble : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EnsembleName;
    
    USQEX_AnimNotifyState_Bonamik_Ensemble();

};

