#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionChocoboIconBase.h"
#include "EndFieldActionChocoboClimbActor.generated.h"

class UEndFieldActionTriggerComponent;
class UEndNavModifierComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldActionChocoboClimbActor : public AEndFieldActionChocoboIconBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* EnterVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* ExitVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavModifierComponent* ModifierVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ClimbNormalAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ClimbCharacterNormalAngle;
    
public:
    AEndFieldActionChocoboClimbActor(const FObjectInitializer& ObjectInitializer);

};

