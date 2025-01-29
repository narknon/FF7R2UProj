#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndPeekCameraDrawComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndPeekCameraDrawComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndPeekCameraDrawComponent(const FObjectInitializer& ObjectInitializer);

};

