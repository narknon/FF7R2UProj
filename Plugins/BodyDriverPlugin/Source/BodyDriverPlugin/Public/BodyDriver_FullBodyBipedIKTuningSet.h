#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BodyDriver_FullBodyBipedIKTuningSet.generated.h"

UCLASS(Blueprintable)
class BODYDRIVERPLUGIN_API UBodyDriver_FullBodyBipedIKTuningSet : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool UseFullBodyBipedIK;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool UseFabrik;
    
    UBodyDriver_FullBodyBipedIKTuningSet();

};

