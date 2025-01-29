#pragma once
#include "CoreMinimal.h"
#include "EndGambitAIController.h"
#include "EndGambitEnemyAIController.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndGambitEnemyAIController : public AEndGambitAIController {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_DefaultGambitPreset;
    
    AEndGambitEnemyAIController(const FObjectInitializer& ObjectInitializer);

};

