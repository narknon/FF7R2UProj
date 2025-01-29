#pragma once
#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "Components/Widget.h"
#include "EndFlagGrid.generated.h"

UCLASS(Blueprintable)
class UEndFlagGrid : public UWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateBrush DefaultBrush;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateBrush FlagBrush;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateBrush CardBrush;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateBrush SpecialEffectBrush;
    
    UEndFlagGrid();

};

