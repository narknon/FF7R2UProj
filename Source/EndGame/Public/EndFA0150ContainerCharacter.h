#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADSoundKey.h"
#include "EndCharacter.h"
#include "EndFA0150ContainerCharacter.generated.h"

class USQEXSEADSound;

UCLASS(Blueprintable)
class ENDGAME_API AEndFA0150ContainerCharacter : public AEndCharacter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADSoundKey PutOnFloor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADSoundKey PutOnContainer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AttachBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADSoundKey EnvironmentHit;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADSoundKey ContainerHit;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* PutOnFloorSoundAsset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* PutOnContainerSoundAsset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* EnvironmentHitSoundAsset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* ContainerHitSoundAsset;
    
public:
    AEndFA0150ContainerCharacter(const FObjectInitializer& ObjectInitializer);

};

