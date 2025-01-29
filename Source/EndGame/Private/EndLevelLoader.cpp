#include "EndLevelLoader.h"

UEndLevelLoader::UEndLevelLoader() {
}

void UEndLevelLoader::WaitStreamLevelEmpty(const UObject* WorldContextObject, FLatentActionInfo LatentInfo) {
}

void UEndLevelLoader::UnLoadStreamLevelSpec(const UObject* WorldContextObject, int32 Priority, FName SpecName, FLatentActionInfo LatentInfo) {
}

void UEndLevelLoader::UnloadStreamLevelSingle(const UObject* WorldContextObject, int32 Priority, FName LevelNames, FLatentActionInfo LatentInfo) {
}

void UEndLevelLoader::UnloadStreamLevelGroups(const UObject* WorldContextObject, int32 Priority, TArray<FName> LevelNames, FLatentActionInfo LatentInfo) {
}

FString UEndLevelLoader::MakeLongLevelName(const FString& ShortName) {
    return TEXT("");
}

void UEndLevelLoader::LoadStreamLevelSpec(const UObject* WorldContextObject, int32 Priority, FName SpecName, FLatentActionInfo LatentInfo) {
}

void UEndLevelLoader::LoadStreamLevelSingle(const UObject* WorldContextObject, int32 Priority, FName LevelNames, FLatentActionInfo LatentInfo) {
}

void UEndLevelLoader::LoadStreamLevelGroups(const UObject* WorldContextObject, int32 Priority, TArray<FName> LevelNames, FLatentActionInfo LatentInfo) {
}

AEndCharacterBase* UEndLevelLoader::FindCharacterFromWorld(FName ActorName) {
    return NULL;
}

AEndCharacterBase* UEndLevelLoader::FindCharacterFromLevel(FName LevelName, FName ActorName) {
    return NULL;
}

AActor* UEndLevelLoader::FindActorFromWorld(FName ActorName, const EEndRenderingScene rendering_scene) {
    return NULL;
}

AActor* UEndLevelLoader::FindActorFromLevel(FName LevelName, FName ActorName, const EEndRenderingScene rendering_scene) {
    return NULL;
}


