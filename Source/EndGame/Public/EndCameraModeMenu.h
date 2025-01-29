#pragma once
#include "CoreMinimal.h"
#include "EndMenuCameraModeFrameSelection.h"
#include "EndMenuColorCorrectionSelection.h"
#include "EndUserWidget.h"
#include "EndCameraModeMenu.generated.h"

class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndCameraModeMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndMenuColorCorrectionSelection> ColorCorrectionSelections;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndMenuCameraModeFrameSelection> FrameSelections;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndTextBlock* KeyGuideTextBlock;
    
public:
    UEndCameraModeMenu();

};

