#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/LatentActionManager.h"
#include "EEndRenderingScene.h"
#include "EndLevelLoader.generated.h"

class AActor;
class AEndCharacterBase;

UCLASS(Blueprintable)
class UEndLevelLoader : public UObject {
    GENERATED_BODY()
public:
    UEndLevelLoader();

    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    static void WaitStreamLevelEmpty(const UObject* WorldContextObject, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    static void UnLoadStreamLevelSpec(const UObject* WorldContextObject, int32 Priority, FName SpecName, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    static void UnloadStreamLevelSingle(const UObject* WorldContextObject, int32 Priority, FName LevelNames, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    static void UnloadStreamLevelGroups(const UObject* WorldContextObject, int32 Priority, TArray<FName> LevelNames, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable)
    static FString MakeLongLevelName(const FString& ShortName);
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    static void LoadStreamLevelSpec(const UObject* WorldContextObject, int32 Priority, FName SpecName, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    static void LoadStreamLevelSingle(const UObject* WorldContextObject, int32 Priority, FName LevelNames, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    static void LoadStreamLevelGroups(const UObject* WorldContextObject, int32 Priority, TArray<FName> LevelNames, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable)
    static AEndCharacterBase* FindCharacterFromWorld(FName ActorName);
    
    UFUNCTION(BlueprintCallable)
    static AEndCharacterBase* FindCharacterFromLevel(FName LevelName, FName ActorName);
    
    UFUNCTION(BlueprintCallable)
    static AActor* FindActorFromWorld(FName ActorName, const EEndRenderingScene rendering_scene);
    
    UFUNCTION(BlueprintCallable)
    static AActor* FindActorFromLevel(FName LevelName, FName ActorName, const EEndRenderingScene rendering_scene);
    
};

