#include "EOSSettings.h"

UEOSSettings::UEOSSettings() {
    this->CacheDir = TEXT("CacheDir");
    this->DefaultArtifactName = TEXT("33e6ac38b5a14098b079fd62d71aabc6");
    this->TickBudgetInMilliseconds = 0;
    this->bEnableOverlay = true;
    this->bEnableSocialOverlay = true;
    this->bShouldEnforceBeingLaunchedByEGS = false;
    this->TitleStorageReadChunkLength = 0;
    this->Artifacts.AddDefaulted(1);
    this->bUseEAS = true;
    this->bUseEOSConnect = false;
    this->bMirrorStatsToEOS = false;
    this->bMirrorAchievementsToEOS = false;
    this->bUseEOSSessions = false;
    this->bMirrorPresenceToEAS = false;
}


