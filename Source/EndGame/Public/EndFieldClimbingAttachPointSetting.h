#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldClimbingCatchPointSetting.h"
#include "EndFieldClimbingAttachPointSetting.generated.h"

UCLASS(Blueprintable, EditInlineNew, HideDropdown, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldClimbingAttachPointSetting : public UEndFieldClimbingCatchPointSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bStartOrFinishPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bStartIsTopEdge;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisbleStart;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AIBPActionTag_Finish;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform GuidEffectTransform;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ForcEnableCatchNameArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ForceDisableCatchNameArray;
    
    UEndFieldClimbingAttachPointSetting(const FObjectInitializer& ObjectInitializer);

};

