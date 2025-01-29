#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndLockOnSiteDrawComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndLockOnSiteDrawComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndLockOnSiteDrawComponent(const FObjectInitializer& ObjectInitializer);

};

