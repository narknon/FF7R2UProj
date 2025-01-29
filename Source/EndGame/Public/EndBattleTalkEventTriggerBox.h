#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EndBattleTalkEventTriggerBox.generated.h"

UCLASS(Blueprintable)
class AEndBattleTalkEventTriggerBox : public ATriggerBox {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName battleSceneID;
    
    AEndBattleTalkEventTriggerBox(const FObjectInitializer& ObjectInitializer);

};

