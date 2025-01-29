#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EndGridLayoutLevelInfo.h"
#include "EndGridLayoutInfo.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndGridLayoutInfo : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndGridLayoutLevelInfo> GridLayoutLevels;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float GridSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LoadDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float UnloadMargin;
    
    UEndGridLayoutInfo();

};

