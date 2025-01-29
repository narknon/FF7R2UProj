#include "EndTextResource.h"

UEndTextResource::UEndTextResource() {
}

FEndTextResourceInfo UEndTextResource::GetTextInfo(const FString& InTextId) const {
    return FEndTextResourceInfo{};
}

FString UEndTextResource::GetText(const FString& InTextId) const {
    return TEXT("");
}


