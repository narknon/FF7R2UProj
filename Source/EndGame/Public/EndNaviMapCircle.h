#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "Components/Widget.h"
#include "EndNaviMapCircle.generated.h"

class UEndNaviMapPrototypeDataV2;
class UTextureRenderTarget2D;

UCLASS(Blueprintable)
class ENDGAME_API UEndNaviMapCircle : public UWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PixelPerCm;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D NaviMapSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 NumSides;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndNaviMapPrototypeDataV2* PrototypeDataV2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UTextureRenderTarget2D* RenderTexture;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UTextureRenderTarget2D* MaskTexture;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    TArray<UWidget*> IconWidgets;
    
public:
    UEndNaviMapCircle();

    UFUNCTION(BlueprintCallable)
    void SetPosition3D(const FVector& InPos);
    
    UFUNCTION(BlueprintCallable)
    FVector2D ConvertToPosition2D(const FVector& InPos);
    
};

