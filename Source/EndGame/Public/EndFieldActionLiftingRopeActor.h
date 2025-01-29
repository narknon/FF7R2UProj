#pragma once
#include "CoreMinimal.h"
#include "ELiftingRopeActorMoveType.h"
#include "EndFieldActionSaveActorBase.h"
#include "EndFieldLiftingRopeAnimSetting.h"
#include "EndFieldActionLiftingRopeActor.generated.h"

class UEndFieldActionTriggerCustomComponent;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionLiftingRopeActor : public AEndFieldActionSaveActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ELiftingRopeActorMoveType MoveType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerCustomComponent* LowerEnterVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerCustomComponent* UpperEnterVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldLiftingRopeAnimSetting Anim_PlayerStartSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldLiftingRopeAnimSetting Anim_PlayerStartSetting_Down;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldLiftingRopeAnimSetting Anim_PlayerLoopSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldLiftingRopeAnimSetting Anim_PlayerLoopSetting_Down;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldLiftingRopeAnimSetting Anim_PlayerEndSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldLiftingRopeAnimSetting Anim_PlayerEndSetting_Down;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LeaveAngle;
    
public:
    AEndFieldActionLiftingRopeActor(const FObjectInitializer& ObjectInitializer);

};

