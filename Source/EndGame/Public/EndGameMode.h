#pragma once
#include "CoreMinimal.h"
#include "EndCoreGameMode.h"
#include "Engine/LatentActionManager.h"
#include "BootMenuLaunchDelegateDelegate.h"
#include "EndGameMode.generated.h"

class AEndGameJumpActor;
class AEndPartyCoordinator;
class UEndCrossSaveManager;
class UEndOneSaveDataManager;
class UObject;
class UUserWidget;

UCLASS(Blueprintable, NonTransient)
class ENDGAME_API AEndGameMode : public AEndCoreGameMode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool DebugGameMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool DebugGameMode_Normal;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 DebugGameModeFlags;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool GamePlayMode;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint64 TotalTickTime;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint64 FrameTickTime;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint64 FrameTickCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SystemDeltaTimeSeconds;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBootMenuLaunchDelegate BootMenuLaunchDelegate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSet<UObject*> ReferenceAssets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TSet<UObject*> ReferenceObjects;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UObject*> OnUnloadEnvLevelAssetReferences;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndCrossSaveManager* CrossSaveManager;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndOneSaveDataManager* EndOneSaveDataManager;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UUserWidget* SequenceAppContentWidget;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndGameJumpActor* GameJumpActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndPartyCoordinator* PartyCoordinator;
    
    AEndGameMode(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    static void InitEditorPreviewGameMode(const UObject* WorldContextObject, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    static void InitEditorGameMode(const UObject* WorldContextObject, FName LocationName, bool QuickStart, FName InCutName, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable)
    void InitBootSequence();
    
};

