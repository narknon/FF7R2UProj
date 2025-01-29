#pragma once
#include "CoreMinimal.h"
#include "NavigationSystem.h"
#include "EndNavigationSystem.generated.h"

UCLASS(Blueprintable, NonTransient)
class ENDGAME_API UEndNavigationSystem : public UNavigationSystemV1 {
    GENERATED_BODY()
public:
    UEndNavigationSystem();

};

