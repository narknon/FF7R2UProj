#pragma once
#include "CoreMinimal.h"
#include "EPlayerType.h"
#include "EndUserWidget.h"
#include "EndPlayerStatusPanel.generated.h"

class UEndCanvasPanel;

UCLASS(Blueprintable, EditInlineNew)
class UEndPlayerStatusPanel : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* All_TopStatus_List;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Nut_Sp;
    
    UEndPlayerStatusPanel();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnSetupStatusPanel(EPlayerType PlayerType);
    
};

