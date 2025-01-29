#include "EndTextResourceAPI.h"

UEndTextResourceAPI::UEndTextResourceAPI() {
}

FString UEndTextResourceAPI::GetTextResourceText(const FString& InTextId, const FString& InLanguage) {
    return TEXT("");
}

FEndTextResourceInfo UEndTextResourceAPI::GetTextResourceInfo(const FString& InTextId, const FString& InLanguage) {
    return FEndTextResourceInfo{};
}


