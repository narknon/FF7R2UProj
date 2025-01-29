#pragma once
#include "CoreMinimal.h"
#include "EEndOneShotMoveDirType.h"
#include "EEndOneShotMoveType.h"
#include "EndFieldActionSaveActorBase.h"
#include "EndFieldOneShotMoveSetting.h"
#include "EndFieldActionOneShotMoveActor.generated.h"

class UEndFieldActionTriggerComponent;
class UEndFieldActionTriggerCustomComponent;
class UEndNavWorldLinkAttrIgnoreBoxComponent;
class UEndSwitchAreaBoxComponent;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionOneShotMoveActor : public AEndFieldActionSaveActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* TikableVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndOneShotMoveType MoveType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerCustomComponent* RightEnterVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerCustomComponent* LeftEnterVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndOneShotMoveDirType OneShotDirType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bHideEnterIcon;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavWorldLinkAttrIgnoreBoxComponent* RightWorldLinkIgnoreVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavWorldLinkAttrIgnoreBoxComponent* LeftWorldLinkIgnoreVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseImpassableVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSwitchAreaBoxComponent* NavImpassableVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldOneShotMoveSetting Interact_StartAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldOneShotMoveSetting Interact_StartAnimationPlayer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldOneShotMoveSetting Interact_ReturnAnimationPlayer;
    
public:
    AEndFieldActionOneShotMoveActor(const FObjectInitializer& ObjectInitializer);

};

