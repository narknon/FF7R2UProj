#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Widgets/Layout/Anchors.h"
#include "Layout/Margin.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelSlot.h"
#include "EndCanvasPanelSlot.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndCanvasPanelSlot : public UPanelSlot {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FAnchorData LayoutData;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAutoSize;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDelayedBuild;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ZOrder;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float XAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float YAngle;
    
    UEndCanvasPanelSlot();

    UFUNCTION(BlueprintCallable)
    void SetZOrder(int32 InZOrder);
    
    UFUNCTION(BlueprintCallable)
    void SetYAngle(float InYAngle);
    
    UFUNCTION(BlueprintCallable)
    void SetXAngle(float InYAngle);
    
    UFUNCTION(BlueprintCallable)
    void SetSize(FVector2D InSize);
    
    UFUNCTION(BlueprintCallable)
    void SetPosition(FVector2D InPosition);
    
    UFUNCTION(BlueprintCallable)
    void SetOffsets(FMargin InOffset);
    
    UFUNCTION(BlueprintCallable)
    void SetMinimum(FVector2D InMinimumAnchors);
    
    UFUNCTION(BlueprintCallable)
    void SetMaximum(FVector2D InMaximumAnchors);
    
    UFUNCTION(BlueprintCallable)
    void SetLayout(const FAnchorData& InLayoutData);
    
    UFUNCTION(BlueprintCallable)
    void SetAutoSize(bool InbAutoSize);
    
    UFUNCTION(BlueprintCallable)
    void SetAnchors(FAnchors InAnchors);
    
    UFUNCTION(BlueprintCallable)
    void SetAlignment(FVector2D InAlignment);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetZOrder() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetYAngle() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetXAngle() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector2D GetSize() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector2D GetPosition() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FMargin GetOffsets() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FAnchorData GetLayout() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool GetAutoSize() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FAnchors GetAnchors() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector2D GetAlignment() const;
    
};

