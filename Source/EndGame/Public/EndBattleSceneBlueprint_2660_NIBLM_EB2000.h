#pragma once
#include "CoreMinimal.h"
#include "EndBattleSceneBlueprint.h"
#include "EndBattleSceneBlueprint_2660_NIBLM_EB2000.generated.h"

UCLASS(Blueprintable)
class AEndBattleSceneBlueprint_2660_NIBLM_EB2000 : public AEndBattleSceneBlueprint {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> StalactiteActorGroupIDList;
    
    AEndBattleSceneBlueprint_2660_NIBLM_EB2000(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void RestoreStalactite();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetTotalStalactiteNum() const;
    
    UFUNCTION(BlueprintCallable)
    void FallStalactite();
    
};

