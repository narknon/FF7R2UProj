#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "EndBikeControllerBase.generated.h"

UCLASS(Abstract, Blueprintable)
class AEndBikeControllerBase : public AActor {
    GENERATED_BODY()
public:
    AEndBikeControllerBase(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void GetTargetFieldPosition(FVector& OutPosition, FName InBattleAbilityID, FName InDamageSourceID, FName InAnimationName);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void GetCreateFieldPosition(FVector& OutPosition, FName InBattleAbilityID, FName InDamageSourceID, FName InAnimationName);
    
};

