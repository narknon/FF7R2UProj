#pragma once
#include "CoreMinimal.h"
#include "EndTriggerBox.h"
#include "EndDirectionalTriggerBox.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndDirectionalTriggerBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName FrontTriggerName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BackTriggerName;
    
    AEndDirectionalTriggerBox(const FObjectInitializer& ObjectInitializer);

};

