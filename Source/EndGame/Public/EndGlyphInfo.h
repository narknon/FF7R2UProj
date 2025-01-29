#pragma once
#include "CoreMinimal.h"
#include "EndGlyphInfo.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndGlyphInfo {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint16 TextureIndex;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint16 TextureX;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint16 TextureY;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint16 SizeX;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint16 SizeY;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int16 HorizontalOffset;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int16 VerticalOffset;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int16 XAdvance;
    
    FEndGlyphInfo();
};

