#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndSequencerWrapperBase.generated.h"

class ULevelSequence;

UCLASS(Blueprintable, Transient)
class ENDGAME_API UEndSequencerWrapperBase : public UObject {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ULevelSequence* LevelSequence;
    
public:
    UEndSequencerWrapperBase();

};

