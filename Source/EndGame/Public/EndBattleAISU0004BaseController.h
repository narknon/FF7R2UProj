#pragma once
#include "CoreMinimal.h"
#include "EndBattleAISummonBaseController.h"
#include "EndBattleAISU0004BaseController.generated.h"

UCLASS(Blueprintable)
class AEndBattleAISU0004BaseController : public AEndBattleAISummonBaseController {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> FlyModeBattleSceneID;
    
public:
    AEndBattleAISU0004BaseController(const FObjectInitializer& ObjectInitializer);

};

