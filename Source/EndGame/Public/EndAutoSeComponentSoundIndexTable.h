#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EndAutoSeComponentAssetTableNonAttribute.h"
#include "EndAutoSeComponentAssetTablePerAttribute.h"
#include "EndAutoSeComponentSoundIndexTable.generated.h"

UCLASS(Blueprintable)
class UEndAutoSeComponentSoundIndexTable : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAutoSeComponentAssetTablePerAttribute PerAttribute[38];
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAutoSeComponentAssetTableNonAttribute NonAttribute;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PerAttributeCustomPitch;
    
    UEndAutoSeComponentSoundIndexTable();

};

