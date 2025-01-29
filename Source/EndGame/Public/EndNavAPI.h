#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "AI/Navigation/NavigationTypes.h"
#include "EEndNavLayerType.h"
#include "EEndQueryFilterType.h"
#include "EndNavAPI.generated.h"

class AEndNavModifierVolume;

UCLASS(Blueprintable)
class ENDGAME_API UEndNavAPI : public UObject {
    GENERATED_BODY()
public:
    UEndNavAPI();

    UFUNCTION(BlueprintCallable)
    static bool ValidateNavModifierVolume(const FName ActorName);
    
    UFUNCTION(BlueprintCallable)
    static bool ValidateFieldActionModifierVolume(const FName ActorName);
    
    UFUNCTION(BlueprintCallable)
    static bool ValidateBlockingModifierVolume(const FName LevelName, const FName ActorName);
    
    UFUNCTION(BlueprintCallable)
    static bool ValidateAerialIgnoreVolume(const FName ActorName);
    
    UFUNCTION(BlueprintCallable)
    static bool InvalidateNavModifierVolume(const FName ActorName);
    
    UFUNCTION(BlueprintCallable)
    static bool InvalidateFieldActionModifierVolume(const FName ActorName);
    
    UFUNCTION(BlueprintCallable)
    static bool InvalidateBlockingModifierVolume(const FName LevelName, const FName ActorName);
    
    UFUNCTION(BlueprintCallable)
    static bool InvalidateAerialIgnoreVolume(const FName ActorName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FTransform GetNavModifierTransform(const FName Name);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndNavModifierVolume* GetNavFromName(const FName Name);
    
    UFUNCTION(BlueprintCallable)
    static FNavAgentProperties GetAgentPropety(EEndNavLayerType InLayerType);
    
    UFUNCTION(BlueprintCallable)
    static bool FindNearestNavMeshPointAgent(FVector TargetLocation, FVector& OutLocation, FName InModifierName, FNavAgentProperties InAgentProperty, FVector SearchRange, EEndQueryFilterType FilterType);
    
    UFUNCTION(BlueprintCallable)
    static bool FindNearestNavMeshPoint(FVector TargetLocation, FVector& OutLocation, FName InModifierName, FVector SearchRange, EEndQueryFilterType FilterType);
    
    UFUNCTION(BlueprintCallable)
    static void DisableNavStreaming(bool Disabled);
    
};

