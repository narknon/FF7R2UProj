#pragma once
#include "CoreMinimal.h"
#include "EndAssetSoftActor.h"
#include "EndAssetTextActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndAssetTextActor : public AEndAssetSoftActor {
    GENERATED_BODY()
public:
    AEndAssetTextActor(const FObjectInitializer& ObjectInitializer);

};

