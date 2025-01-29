#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndWeaponSkeletalMeshActor.h"
#include "EndBattleDamageSourceActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndBattleDamageSourceActor : public AEndWeaponSkeletalMeshActor {
    GENERATED_BODY()
public:
    AEndBattleDamageSourceActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetMoveDir() const;
    
};

