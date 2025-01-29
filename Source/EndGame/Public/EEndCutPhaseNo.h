#pragma once
#include "CoreMinimal.h"
#include "EEndCutPhaseNo.generated.h"

UENUM(BlueprintType)
enum class EEndCutPhaseNo : uint8 {
    Nothing,
    LevelLoading,
    FastReloading,
    CharaSpecLoading,
    ActorCreating,
    LoadStreamingVolume,
    WaitStreamingVolume,
    WaitTimeSet,
    WaitPreviewLast,
    WaitPlaying,
    WaitOnActorCreated,
    WaitOpenMovie,
    Playing,
    WaitFinished,
    Finished,
    ReadyPlayMovie,
    WaitPlayMovie,
    WaitMediaSourceOpened,
    WaitInEventMovie,
    MiddleCreateActor,
};

