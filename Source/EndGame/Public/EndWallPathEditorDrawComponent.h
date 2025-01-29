#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndWallPathEditorDrawComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndWallPathEditorDrawComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndWallPathEditorDrawComponent(const FObjectInitializer& ObjectInitializer);

};

