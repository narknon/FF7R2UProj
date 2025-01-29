#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SQEXSEADSoundBank.generated.h"

class UAssetImportData;

UCLASS(Blueprintable, EditInlineNew, MinimalAPI)
class USQEXSEADSoundBank : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UAssetImportData* AssetImportData;
    
    USQEXSEADSoundBank();

};

