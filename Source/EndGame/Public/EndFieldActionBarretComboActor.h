#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldActionCommonActorBase.h"
#include "EndFieldBarretComboSettingBase.h"
#include "EndFieldActionBarretComboActor.generated.h"

class UEndFieldActionTriggerComponent;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionBarretComboActor : public AEndFieldActionCommonActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* TikableVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform PlayerTransform;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform IconTransform;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform ComboIconTransform;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 HotFixComboNum;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldBarretComboSettingBase> ComboSetting;
    
public:
    AEndFieldActionBarretComboActor(const FObjectInitializer& ObjectInitializer);

};

