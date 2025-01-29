#pragma once
#include "CoreMinimal.h"
#include "EndSequencerWrapperMovieBase.h"
#include "EndSequencerWrapperMovie.generated.h"

class UMediaSource;

UCLASS(Blueprintable, NonTransient)
class UEndSequencerWrapperMovie : public UEndSequencerWrapperMovieBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UMediaSource* DuplicatedLoadingMediaSource;
    
public:
    UEndSequencerWrapperMovie();

};

