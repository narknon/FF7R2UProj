#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndCutAPI.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndCutAPI : public UObject {
    GENERATED_BODY()
public:
    UEndCutAPI();

    UFUNCTION(BlueprintCallable)
    static bool IsPreview();
    
};

