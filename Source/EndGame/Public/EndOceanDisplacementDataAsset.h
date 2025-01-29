#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EndOceanDisplacementDataAsset.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndOceanDisplacementDataAsset : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> OceanMagnitudeData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 SizeX;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 SizeY;
    
    UEndOceanDisplacementDataAsset();

};

