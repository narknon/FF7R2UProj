#include "MovieSceneEndEventTrack.h"

UMovieSceneEndEventTrack::UMovieSceneEndEventTrack() {
    this->bFireEventsWhenForwards = true;
    this->bFireEventsWhenBackwards = true;
    this->EventPosition = EEndFireEventsAtPosition::AfterSpawn;
}


