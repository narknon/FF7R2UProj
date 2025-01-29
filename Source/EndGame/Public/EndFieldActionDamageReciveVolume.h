#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionDamageReciveVolumeBase.h"
#include "EndFieldActionDamageReciveVolume.generated.h"

class UEndFieldActionDamageReciveComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndFieldActionDamageReciveVolume : public AEndFieldActionDamageReciveVolumeBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CollisionControlByStoryFlag;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionDamageReciveComponent* DamageReciveComponent;
    
    AEndFieldActionDamageReciveVolume(const FObjectInitializer& ObjectInitializer);

};

