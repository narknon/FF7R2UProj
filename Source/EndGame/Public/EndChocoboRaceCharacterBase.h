#pragma once
#include "CoreMinimal.h"
#include "EndChocoboRaceCharacterBase.generated.h"

class AEndCharacterBase;

USTRUCT(BlueprintType)
struct FEndChocoboRaceCharacterBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TWeakObjectPtr<AEndCharacterBase>> CourseOutMoogle;
    
public:
    ENDGAME_API FEndChocoboRaceCharacterBase();
};

