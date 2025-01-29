#pragma once
#include "CoreMinimal.h"
#include "EndBattleAISummonBaseController.h"
#include "EndBattleAISU0005BaseController.generated.h"

UCLASS(Blueprintable)
class AEndBattleAISU0005BaseController : public AEndBattleAISummonBaseController {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EXModeTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString EXAbilityPostfix;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PathFindHeight;
    
public:
    AEndBattleAISU0005BaseController(const FObjectInitializer& ObjectInitializer);

};

