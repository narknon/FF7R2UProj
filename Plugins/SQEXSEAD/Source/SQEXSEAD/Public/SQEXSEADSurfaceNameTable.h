#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SQEXSEADSurfaceNameTable.generated.h"

UCLASS(Blueprintable)
class SQEXSEAD_API USQEXSEADSurfaceNameTable : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Names[63];
    
    USQEXSEADSurfaceNameTable();

};

