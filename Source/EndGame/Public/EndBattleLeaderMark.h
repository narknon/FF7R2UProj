#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndBattleLeaderMark.generated.h"

class UEndCanvasPanel;

UCLASS(Blueprintable, EditInlineNew)
class UEndBattleLeaderMark : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Nut_BattleLeaderMark;
    
    UEndBattleLeaderMark();

};

