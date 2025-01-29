#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EWeaponSlot.h"
#include "EndSceneAPI.generated.h"

class AActor;
class AEndNavModifierVolume;
class UMaterialInterface;
class UMediaPlayer;
class UMediaTexture;

UCLASS(Blueprintable)
class ENDGAME_API UEndSceneAPI : public UObject {
    GENERATED_BODY()
public:
    UEndSceneAPI();

    UFUNCTION(BlueprintCallable)
    static bool ValidateSimpleCameraWall(FName TargetActorName);
    
    UFUNCTION(BlueprintCallable)
    static bool TeleportActor(FName LevelName, FName ActorName, AActor* TargetActor, bool bApplyDestRotation);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsDrawPause(AActor* Actor);
    
    UFUNCTION(BlueprintCallable)
    static bool InvalidateSimpleCameraWall(FName TargetActorName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FTransform GetNavTransformFromLevel(FName Level, FName Name);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FTransform GetNavTransform(FName Name);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FRotator GetNavRotationFromLevel(FName Level, FName Name);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FRotator GetNavRotation(FName Name);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FVector GetNavLocationFromLevel(FName Level, FName Name);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FVector GetNavLocation(FName Name);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndNavModifierVolume* GetNavFromNameAndLevel(FName Level, FName Name);
    
    UFUNCTION(BlueprintCallable)
    static bool FindMediaPlayer(const UMaterialInterface* MovieMaterial, UMediaPlayer*& OutMediaPlayer, UMediaTexture*& OutMediaTexture);
    
    UFUNCTION(BlueprintCallable)
    static UMaterialInterface* FindMaterialByName(AActor* Actor, FName MaterialName);
    
    UFUNCTION(BlueprintCallable)
    static AActor* FindActorFromAccessorBP(FName InAccessId, FName InLevelName, FName InAccsessorActorName);
    
    UFUNCTION(BlueprintCallable)
    static void DetachWeapon(AActor* CharacterActor, EWeaponSlot Slot);
    
    UFUNCTION(BlueprintCallable)
    static int32 DestroyActorBP(FName Name);
    
    UFUNCTION(BlueprintCallable)
    static int32 CreateActorBP(FName Name, FName CharaSpec, FVector Location, FRotator Rotation);
    
    UFUNCTION(BlueprintCallable)
    static void AttachWeapon(AActor* CharacterActor, AActor* WeaponActor, EWeaponSlot Slot);
    
};

