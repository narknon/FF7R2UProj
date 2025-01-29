#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ESQEXSEAD_BGMState.h"
#include "SQEXSEAD_BGMOptions.h"
#include "SQEXSEADBGMSlot.generated.h"

class USQEXSEAD_BGM;

UCLASS(Blueprintable)
class SQEXSEAD_API USQEXSEADBGMSlot : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ESQEXSEAD_BGMState State;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEAD_BGMOptions DefaultOptions_;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEAD_BGM* BGM_;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<USQEXSEAD_BGM*> FadeOutBGMs_;
    
public:
    USQEXSEADBGMSlot();

};

