#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateColor.h"
#include "Components/Widget.h"
#include "EndBillboard.generated.h"

class UEndUserWidget;
class UMaterialInstance;

UCLASS(Blueprintable)
class UEndBillboard : public UWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftObjectPath ImagePath;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D ImageSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateColor TintColor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESlateBrushDrawType::Type> DrawAs;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESlateBrushTileType::Type> Tiling;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor ColorAndOpacity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UWidget::FGetLinearColor ColorAndOpacityDelegate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EBlendMode> BlendMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAutoLoad;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UWidget::FOnPointerEvent OnMouseButtonDownEvent;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FSlateBrush Brush;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndUserWidget* Throbber;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UMaterialInstance* MovieMaterial;
    
public:
    UEndBillboard();

    UFUNCTION(BlueprintCallable)
    void SetOpacity(float InOpacity);
    
    UFUNCTION(BlueprintCallable)
    void SetImagePath(FSoftObjectPath InImagePath, bool bInRewind, bool bInLoop);
    
    UFUNCTION(BlueprintCallable)
    void SetImageAssetNameString(const FString& InAssetName, bool bInRewind, bool bInLoop);
    
    UFUNCTION(BlueprintCallable)
    void SetImageAssetName(FName InAssetName, bool bInRewind, bool bInLoop);
    
    UFUNCTION(BlueprintCallable)
    void SetColorAndOpacity(FLinearColor InColorAndOpacity);
    
    UFUNCTION(BlueprintCallable)
    void SetBlendMode(TEnumAsByte<EBlendMode> InBlendMode);
    
    UFUNCTION(BlueprintCallable)
    static FSoftObjectPath MakeImagePathFromAssetNameString(const FString& InAssetName);
    
    UFUNCTION(BlueprintCallable)
    static FSoftObjectPath MakeImagePathFromAssetName(FName InAssetName);
    
};

