#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EEndAIRecognitionVolumeType.h"
#include "EndAIRecognitionVolumeInterface.h"
#include "EndAIRecognitionVolume.generated.h"

class UEndAIRecognitionBoxComponent;

UCLASS(Blueprintable)
class AEndAIRecognitionVolume : public AActor, public IEndAIRecognitionVolumeInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIRecognitionVolumeType VolumeType;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 GroupId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndAIRecognitionBoxComponent* RecognitionBoxComponent;
    
public:
    AEndAIRecognitionVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

