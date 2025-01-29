#pragma once
#include "CoreMinimal.h"
#include "Rigs/RigHierarchyDefines.h"
#include "RigUnit_EndAim_EffectorItem.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndAim_EffectorItem {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigElementKey Item;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float UpRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUpOnly;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TranslationRate;
    
    ENDGAME_API FRigUnit_EndAim_EffectorItem();
};

