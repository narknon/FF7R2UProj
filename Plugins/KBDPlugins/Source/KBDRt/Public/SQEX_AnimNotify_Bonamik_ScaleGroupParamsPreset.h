#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SQEX_AnimNotify_Bonamik_ScaleGroupParamsPreset.generated.h"

class USQEX_Bonamik_ScaleGroupParamsPreset;

UCLASS(Blueprintable, CollapseCategories)
class KBDRT_API USQEX_AnimNotify_Bonamik_ScaleGroupParamsPreset : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> m_Groups;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEX_Bonamik_ScaleGroupParamsPreset* m_Preset;
    
    USQEX_AnimNotify_Bonamik_ScaleGroupParamsPreset();

};

