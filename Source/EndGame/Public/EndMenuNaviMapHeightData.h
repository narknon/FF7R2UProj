#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "EndMenuNaviMapHeightData.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndMenuNaviMapHeightData : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlockSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FIntPoint Blocks;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector BasePosition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, TextExportTransient, meta=(AllowPrivateAccess=true))
    TArray<float> HeightData;
    
    UEndMenuNaviMapHeightData();

};

