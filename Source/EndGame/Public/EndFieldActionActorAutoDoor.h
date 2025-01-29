#pragma once
#include "CoreMinimal.h"
#include "EAutoDoorActiveEffectType.h"
#include "EEndOneWayType.h"
#include "EndFieldActionStateManagedActor.h"
#include "EndFieldActionActorAutoDoor.generated.h"

class UEndFieldActionTriggerCustomComponent;
class UEndNavModifierComponent;
class UEndSwitchAreaBoxComponent;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionActorAutoDoor : public AEndFieldActionStateManagedActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAutoDoorActiveEffectType AutoDoorActiveEffectType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerCustomComponent* OpenVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerCustomComponent* CloseVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerCustomComponent* TickVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSwitchAreaBoxComponent* DividedVersatileVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavModifierComponent* ModifierVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AutoClosingTime;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndOneWayType BattleInWayType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableBattleIn;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCanOpenCutSceneBindChara;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bIgnoreCheck_DisableFieldAction;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDeactiveIsEnableCollision;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bBattleIsAlwaysClose;
    
    AEndFieldActionActorAutoDoor(const FObjectInitializer& ObjectInitializer);

};

