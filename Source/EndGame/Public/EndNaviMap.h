#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "Components/Widget.h"
#include "EndNaviMap.generated.h"

class UEndNaviMapPrototypeDataV2;
class UTextureRenderTarget2D;

UCLASS(Blueprintable)
class UEndNaviMap : public UWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D Size;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PixelPerCm;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndNaviMapPrototypeDataV2* PrototypeDataV2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UTextureRenderTarget2D* MaskTexture;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    TArray<UWidget*> IconWidgets;
    
public:
    UEndNaviMap();

    UFUNCTION(BlueprintCallable)
    void SetPosition3D(const FVector& InPos);
    
    UFUNCTION(BlueprintCallable)
    FVector2D ConvertToPosition2D(const FVector& InPos);
    
};

