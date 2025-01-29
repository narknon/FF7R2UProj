#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndNavWorldLinkAttrIgnoreBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndNavWorldLinkAttrIgnoreBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndNavWorldLinkAttrIgnoreBoxComponent(const FObjectInitializer& ObjectInitializer);

};

