#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/TextureRenderTarget2D.h"
#include "EndNaviMapStateRenderTarget.generated.h"

UCLASS(Blueprintable)
class UEndNaviMapStateRenderTarget : public UTextureRenderTarget2D {
    GENERATED_BODY()
public:
    UEndNaviMapStateRenderTarget();

    UFUNCTION(BlueprintCallable)
    void SetVisited(int32 X, int32 Y, bool bSyncTexture);
    
    UFUNCTION(BlueprintCallable)
    void SetPixel(int32 X, int32 Y, FColor Color);
    
    UFUNCTION(BlueprintCallable)
    bool IsVisited(int32 X, int32 Y);
    
    UFUNCTION(BlueprintCallable)
    FColor GetPixel(int32 X, int32 Y);
    
};

