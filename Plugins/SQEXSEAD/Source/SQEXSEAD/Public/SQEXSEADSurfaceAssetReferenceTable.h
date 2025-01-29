#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SQEXSEADSurfaceAssetReferenceTableData.h"
#include "SQEXSEADSurfaceAssetReferenceTable.generated.h"

UCLASS(Blueprintable)
class SQEXSEAD_API USQEXSEADSurfaceAssetReferenceTable : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADSurfaceAssetReferenceTableData TableData;
    
    USQEXSEADSurfaceAssetReferenceTable();

};

