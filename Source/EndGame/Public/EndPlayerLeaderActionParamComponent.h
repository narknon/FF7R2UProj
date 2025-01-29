#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndPlayerLeaderActionParamComponent.generated.h"

UCLASS(Blueprintable, DefaultConfig, ClassGroup=Custom, Config=Game, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndPlayerLeaderActionParamComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bNewDebugMove;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bFieldNewJumpMode;
    
    UEndPlayerLeaderActionParamComponent(const FObjectInitializer& ObjectInitializer);

};

