#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndBattleSuperArmorNotify.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndBattleSuperArmorNotify : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bFlag;
    
    UEndBattleSuperArmorNotify();

};

