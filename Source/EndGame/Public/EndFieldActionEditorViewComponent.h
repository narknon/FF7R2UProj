#pragma once
#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "EndFieldActionEditorViewComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndFieldActionEditorViewComponent : public UPrimitiveComponent {
    GENERATED_BODY()
public:
    UEndFieldActionEditorViewComponent(const FObjectInitializer& ObjectInitializer);

};

