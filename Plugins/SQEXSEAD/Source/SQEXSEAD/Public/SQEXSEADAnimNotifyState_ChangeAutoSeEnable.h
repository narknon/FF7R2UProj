#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ESQEXSEADChangeAutoSeEnableNotifyEndBehavior.h"
#include "SQEXSEADAutoSeMotionSoundFilter.h"
#include "SQEXSEADAnimNotifyState_ChangeAutoSeEnable.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class SQEXSEAD_API USQEXSEADAnimNotifyState_ChangeAutoSeEnable : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bEnableAutoSeEnableParameters: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bEnableSetting: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ESQEXSEADChangeAutoSeEnableNotifyEndBehavior NotifyEndBehavior;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bEnableContinuousDisabling: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bEnableMotionDetectFilters: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bMotionDetectFilterAsGlobal: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADAutoSeMotionSoundFilter MSFilter;
    
    USQEXSEADAnimNotifyState_ChangeAutoSeEnable();

};

