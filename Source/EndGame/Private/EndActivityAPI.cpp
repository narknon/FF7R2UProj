#include "EndActivityAPI.h"

UEndActivityAPI::UEndActivityAPI() {
}

EEndActivityInitResult UEndActivityAPI::GetActivityInitResult() {
    return EEndActivityInitResult::None;
}

void UEndActivityAPI::ActivityInit(UObject* WorldContextObject, FLatentActionInfo LatentInfo) {
}


