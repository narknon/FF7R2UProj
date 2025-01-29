#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADSound.h"
#include "SQEXSEADMusic.generated.h"

UCLASS(Blueprintable, EditInlineNew, MinimalAPI)
class USQEXSEADMusic : public USQEXSEADSound {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, int32> SectionNameIndexTable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, int32> ModeNameIndexTable;
    
    USQEXSEADMusic();

};

