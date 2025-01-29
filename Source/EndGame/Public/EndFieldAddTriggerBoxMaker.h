#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EndFieldAddTriggerBoxMaker.generated.h"

class UEndFieldActionTriggerCustomComponent;

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldAddTriggerBoxMaker : public USceneComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerCustomComponent* TriggerBox;
    
    UEndFieldAddTriggerBoxMaker(const FObjectInitializer& ObjectInitializer);

};

