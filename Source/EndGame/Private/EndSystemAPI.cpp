#include "EndSystemAPI.h"

UEndSystemAPI::UEndSystemAPI() {
}

void UEndSystemAPI::UpdateCharaPopLODDistance() {
}

bool UEndSystemAPI::IsTrialMode() {
    return false;
}

bool UEndSystemAPI::IsPreviewEventMode() {
    return false;
}

bool UEndSystemAPI::IsPlayableDemoMode() {
    return false;
}

bool UEndSystemAPI::IsMediaDemoMode() {
    return false;
}

bool UEndSystemAPI::IsMaster() {
    return false;
}

bool UEndSystemAPI::IsInWestLocation_End2() {
    return false;
}

bool UEndSystemAPI::IsInputKeyRepeat(FKey Key) {
    return false;
}

bool UEndSystemAPI::IsInputKeyReleased(FKey Key) {
    return false;
}

bool UEndSystemAPI::IsInputKeyPressed(FKey Key) {
    return false;
}

bool UEndSystemAPI::IsInputKeyDown(FKey Key) {
    return false;
}

bool UEndSystemAPI::IsInOceanLocation_End2() {
    return false;
}

bool UEndSystemAPI::IsInNorthLocation_End2() {
    return false;
}

bool UEndSystemAPI::IsInEastLocation_End2() {
    return false;
}

bool UEndSystemAPI::IsExpansion3Mode() {
    return false;
}

bool UEndSystemAPI::IsExpansion2Mode() {
    return false;
}

bool UEndSystemAPI::IsEndGameMode() {
    return false;
}

int32 UEndSystemAPI::GetCurrentLocationNumber_End2() {
    return 0;
}

FName UEndSystemAPI::GetCurrentLocation_End2() {
    return NAME_None;
}

FString UEndSystemAPI::GetCommandLineOptionValue(const FString& Option) {
    return TEXT("");
}

FString UEndSystemAPI::GetBuildTimeString() {
    return TEXT("");
}

FString UEndSystemAPI::GetBuildRevisionString() {
    return TEXT("");
}

void UEndSystemAPI::ForceGarbageCollection() {
}

void UEndSystemAPI::EnableWorldShift(bool bActive) {
}


