#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndPianoButtonWidget.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndPianoButtonWidget : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString ButtonText;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString GuideText;
    
    UEndPianoButtonWidget();

    UFUNCTION(BlueprintCallable)
    void SetTextToWidget(FName WidgetName, const FString& Text);
    
};

