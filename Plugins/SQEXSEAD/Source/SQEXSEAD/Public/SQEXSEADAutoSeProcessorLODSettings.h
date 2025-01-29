#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SQEXSEADAutoSeProcessorLODLevelSettings.h"
#include "SQEXSEADAutoSeProcessorLODSettings.generated.h"

UCLASS(Blueprintable)
class SQEXSEAD_API USQEXSEADAutoSeProcessorLODSettings : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADAutoSeProcessorLODLevelSettings LODLevels[4];
    
    USQEXSEADAutoSeProcessorLODSettings();

};

