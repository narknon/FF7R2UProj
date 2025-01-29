#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SQEXSEADAutoSeComponentInitParams.h"
#include "SQEXSEADAutoSeComponentSetting.generated.h"

UCLASS(Blueprintable)
class SQEXSEAD_API USQEXSEADAutoSeComponentSetting : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADAutoSeComponentInitParams InitParams;
    
    USQEXSEADAutoSeComponentSetting();

};

