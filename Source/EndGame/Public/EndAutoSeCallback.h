#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADAutoSeComponentCallback.h"
#include "EndAutoSeCallback.generated.h"

class UEndAutoSeComponentSoundIndexTable;

UCLASS(Blueprintable, NonTransient)
class UEndAutoSeCallback : public USQEXSEADAutoSeComponentCallback {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UEndAutoSeComponentSoundIndexTable* SoundIndexTable;
    
public:
    UEndAutoSeCallback();

};

