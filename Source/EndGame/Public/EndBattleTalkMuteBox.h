#pragma once
#include "CoreMinimal.h"
#include "EndTriggerBox.h"
#include "EndBattleTalkMuteBox.generated.h"

UCLASS(Blueprintable)
class AEndBattleTalkMuteBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetMembers;
    
    AEndBattleTalkMuteBox(const FObjectInitializer& ObjectInitializer);

};

