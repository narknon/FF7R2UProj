#pragma once
#include "CoreMinimal.h"
#include "EndDialogueSequenceAdditionalAsset.generated.h"

class UObject;

USTRUCT(BlueprintType)
struct ENDGAME_API FEndDialogueSequenceAdditionalAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, UObject*> Assets;
    
    FEndDialogueSequenceAdditionalAsset();
};

