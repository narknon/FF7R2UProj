#pragma once
#include "CoreMinimal.h"
#include "LevelSequence.h"
#include "EEndCutSequencerType.h"
#include "EndCinemaSequence.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndCinemaSequence : public ULevelSequence {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCutSequencerType SequencerType;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName PrimaryPackageLastCutId;
    
    UEndCinemaSequence();

};

