#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Volume.h"
#include "EEndAIRecognitionVolumeShapeType.h"
#include "EEndAIRecognitionVolumeType.h"
#include "EndAIRecognitionVolumeInterface.h"
#include "EndAIRecognitionVolume2.generated.h"

UCLASS(Blueprintable)
class AEndAIRecognitionVolume2 : public AVolume, public IEndAIRecognitionVolumeInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIRecognitionVolumeType VolumeType;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 GroupId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIRecognitionVolumeShapeType ShapeType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Extent;
    
public:
    AEndAIRecognitionVolume2(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

