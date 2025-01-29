#pragma once
#include "CoreMinimal.h"
#include "EEndDialogueSequenceEndShotCamera.h"
#include "EEndDialogueSequenceFirstShotCamera.h"
#include "EndDialogueGenerateSourceActorInitialOverride.h"
#include "EndDialogueGenerateSourceBGFA.h"
#include "EndDialogueGenerateSourceCharacter.h"
#include "EndDialogueGenerateSourceCharacterOverride.h"
#include "EndDialogueGenerateSourceFA.h"
#include "EndDialogueGenerateSourceShot.h"
#include "Templates/SubclassOf.h"
#include "EndDialogueGenerateSource.generated.h"

class UEndDialogueBlueprintGeneratorBase;
class UEndDialogueGenerateSourcePositionPreset;

USTRUCT(BlueprintType)
struct ENDGAME_API FEndDialogueGenerateSource {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LocationId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndDialogueGenerateSourceCharacter> Characters;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndDialogueGenerateSourceFA> FAs;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndDialogueGenerateSourceBGFA> BGFAs;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndDialogueGenerateSourcePositionPreset* PositionPreset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndDialogueGenerateSourceShot> Shots;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUnbindEndShotCamera;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndDialogueSequenceFirstShotCamera FirstShotCamera;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndDialogueSequenceEndShotCamera EndShotCamera;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bReverseCamera;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 OptionalLightCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndDialogueBlueprintGeneratorBase> DefaultCameraGenerator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndDialogueBlueprintGeneratorBase> DefaultMotionGenerator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndDialogueBlueprintGeneratorBase> DefaultLightGenerator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndDialogueGenerateSourceActorInitialOverride> InitialOverride;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FString, FString> MotionRootDirectoryAlias;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> MotionDirectories;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndDialogueGenerateSourceCharacterOverride> DefaultCharacterOverride;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 NextGenerationRetryCount;
    
    FEndDialogueGenerateSource();
};

