#pragma once
#include "CoreMinimal.h"
#include "EndUniqueSimpleCollisionComponent.h"
#include "EndMergedSimpleCollisionComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndMergedSimpleCollisionComponent : public UEndUniqueSimpleCollisionComponent {
    GENERATED_BODY()
public:
    UEndMergedSimpleCollisionComponent(const FObjectInitializer& ObjectInitializer);

};

