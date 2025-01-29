#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Camera/CameraTypes.h"
#include "Components/PanelWidget.h"
#include "Components/Widget.h"
#include "EndCanvasPanel.generated.h"

class UEndCanvasPanelSlot;
class UWidget;

UCLASS(Blueprintable)
class ENDGAME_API UEndCanvasPanel : public UPanelWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor ContentColorAndOpacity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UWidget::FGetLinearColor ContentColorAndOpacityDelegate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bExplicitChildZOrder;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ECameraProjectionMode::Type> ProjectionMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FieldOfView;
    
    UEndCanvasPanel();

    UFUNCTION(BlueprintCallable)
    void SetProjectionMode(TEnumAsByte<ECameraProjectionMode::Type> InProjectionMode);
    
    UFUNCTION(BlueprintCallable)
    void SetFieldOfView(float InFieldOfView);
    
    UFUNCTION(BlueprintCallable)
    void SetExplicitChildZOrder(bool bInExplicitChildZOrder);
    
    UFUNCTION(BlueprintCallable)
    void SetContentColorAndOpacity(FLinearColor InContentColorAndOpacity);
    
    UFUNCTION(BlueprintCallable)
    UEndCanvasPanelSlot* AddChildToCanvas(UWidget* Content);
    
};

