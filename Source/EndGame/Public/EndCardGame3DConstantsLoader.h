#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndCardGame3DConstantsLoader.generated.h"

class UEndCardGame3DConstants;

UCLASS(Blueprintable)
class UEndCardGame3DConstantsLoader : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndCardGame3DConstants* Constants;
    
    UEndCardGame3DConstantsLoader();

};

