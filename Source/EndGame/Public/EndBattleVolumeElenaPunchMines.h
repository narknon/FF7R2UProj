#pragma once
#include "CoreMinimal.h"
#include "EndCliffDataWrapper.h"
#include "EndTriggerBox.h"
#include "EndBattleVolumeElenaPunchMines.generated.h"

class AActor;

UCLASS(Blueprintable)
class ENDGAME_API AEndBattleVolumeElenaPunchMines : public AEndTriggerBox {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCliffDataWrapper> CliffLocations;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bFinalCliff;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 GroupId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<AActor*> CurrentlyOverlappingActors;
    
    AEndBattleVolumeElenaPunchMines(const FObjectInitializer& ObjectInitializer);

};

