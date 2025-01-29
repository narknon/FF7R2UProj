#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelSequenceActor.h"
#include "EndDialogueSequenceActor.generated.h"

class AActor;
class ACineCameraActor;
class AEndCharacterBase;
class AEndDialoguePostProcessControlActor;
class AEndEnvironmentSkeletalMeshActor;
class AEndSkeletalMeshActor;
class ASpotLight;

UCLASS(Blueprintable)
class ENDGAME_API AEndDialogueSequenceActor : public ALevelSequenceActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<ACineCameraActor> CameraActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool bConstraintAspectRatio;
    
    UPROPERTY(EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<TWeakObjectPtr<ASpotLight>> SpotLightActors;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<AEndDialoguePostProcessControlActor> PostProcessControlActor;
    
    UPROPERTY(EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TMap<FName, TWeakObjectPtr<AEndCharacterBase>> BindCharacters;
    
    UPROPERTY(EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<TWeakObjectPtr<AEndCharacterBase>> ActiveCharacters;
    
    UPROPERTY(EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TMap<FName, TWeakObjectPtr<AEndSkeletalMeshActor>> BindFAs;
    
    UPROPERTY(EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<TWeakObjectPtr<AEndSkeletalMeshActor>> ActiveFAs;
    
    UPROPERTY(EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TMap<FName, TWeakObjectPtr<AEndEnvironmentSkeletalMeshActor>> BindBGFAs;
    
    UPROPERTY(EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<TWeakObjectPtr<AEndEnvironmentSkeletalMeshActor>> ActiveBGFAs;
    
    UPROPERTY(EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<TWeakObjectPtr<AActor>> TemporaryActors;
    
    UPROPERTY(EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<TWeakObjectPtr<AActor>> DetectCollisionActors;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TMap<FName, FTransform> InitialTransforms;
    
    AEndDialogueSequenceActor(const FObjectInitializer& ObjectInitializer);

};

