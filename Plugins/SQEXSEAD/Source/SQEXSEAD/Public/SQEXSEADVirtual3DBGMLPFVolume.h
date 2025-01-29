#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "SQEXSEADVirtual3DBGMLPFVolume.generated.h"

UCLASS(Blueprintable)
class SQEXSEAD_API ASQEXSEADVirtual3DBGMLPFVolume : public AVolume {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LPF;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Priority;
    
    ASQEXSEADVirtual3DBGMLPFVolume(const FObjectInitializer& ObjectInitializer);

};

