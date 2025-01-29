#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERenoMineMovementMode.h"
#include "RenoMineAbilityPermissions.h"
#include "RenoMineMovementData.h"
#include "EndAIBattleBossEB0004RenoMineDataComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndAIBattleBossEB0004RenoMineDataComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FRenoMineMovementData> MineMovementData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<ERenoMineMovementMode, FRenoMineAbilityPermissions> AbilityPermissions;
    
    UEndAIBattleBossEB0004RenoMineDataComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetCurrentMineState(ERenoMineMovementMode NewMode);
    
    UFUNCTION(BlueprintCallable)
    ERenoMineMovementMode GetCurrentMineState();
    
    UFUNCTION(BlueprintCallable)
    void FinishRolling(bool ReturnToProwl);
    
};

