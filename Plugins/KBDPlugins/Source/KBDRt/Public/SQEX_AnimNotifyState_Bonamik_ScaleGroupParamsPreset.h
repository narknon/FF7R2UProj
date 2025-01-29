#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SQEX_AnimNotifyState_Bonamik_ScaleGroupParamsPreset.generated.h"

class USQEX_Bonamik_ScaleGroupParamsPreset;

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class KBDRT_API USQEX_AnimNotifyState_Bonamik_ScaleGroupParamsPreset : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> m_Groups;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEX_Bonamik_ScaleGroupParamsPreset* m_Preset;
    
    USQEX_AnimNotifyState_Bonamik_ScaleGroupParamsPreset();

};

