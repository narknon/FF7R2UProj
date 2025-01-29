#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EndFieldAddHookShotAllAngleTriggerBoxMaker.generated.h"

class UEndFieldActionTriggerCustomComponent;

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldAddHookShotAllAngleTriggerBoxMaker : public USceneComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerCustomComponent* TriggerBox;
    
    UEndFieldAddHookShotAllAngleTriggerBoxMaker(const FObjectInitializer& ObjectInitializer);

};

