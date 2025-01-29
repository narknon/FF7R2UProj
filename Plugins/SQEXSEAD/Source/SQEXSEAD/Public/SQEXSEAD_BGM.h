#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SQEXSEAD_BGM.generated.h"

class USQEXSEADSound;

UCLASS(Blueprintable)
class USQEXSEAD_BGM : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* Sound_;
    
    USQEXSEAD_BGM();

};

