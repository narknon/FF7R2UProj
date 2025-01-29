#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EEndCactusMissionMiniGameEnemyType.h"
#include "EndCactusMissionMiniGameEnemyComponent.generated.h"

class AActor;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndCactusMissionMiniGameEnemyComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndCactusMissionMiniGameEnemyComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetHP();
    
    UFUNCTION(BlueprintCallable)
    void PlayEffect(FName ResourceName, AActor* AttachActor, FName AttachSocketName);
    
    UFUNCTION(BlueprintCallable)
    void OnDead(EEndCactusMissionMiniGameEnemyType EnemyType, int32 Score);
    
    UFUNCTION(BlueprintCallable)
    void GetHP();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName GetAssetLoadLevelName() const;
    
};

