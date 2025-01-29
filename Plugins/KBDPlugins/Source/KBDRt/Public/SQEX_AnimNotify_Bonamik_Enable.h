#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SQEX_AnimNotify_Bonamik_Enable.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class KBDRT_API USQEX_AnimNotify_Bonamik_Enable : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> m_Groups;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_On;
    
    USQEX_AnimNotify_Bonamik_Enable();

};

