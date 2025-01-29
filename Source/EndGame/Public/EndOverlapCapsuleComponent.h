#pragma once
#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "EndOverlapCapsuleComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndOverlapCapsuleComponent : public UCapsuleComponent {
    GENERATED_BODY()
public:
    UEndOverlapCapsuleComponent(const FObjectInitializer& ObjectInitializer);

};

