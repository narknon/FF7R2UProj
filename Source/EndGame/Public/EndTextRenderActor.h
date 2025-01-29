#pragma once
#include "CoreMinimal.h"
#include "Engine/TextRenderActor.h"
#include "EndNaviMapDataProviderInterface.h"
#include "EndTextRenderActor.generated.h"

UCLASS(Blueprintable)
class AEndTextRenderActor : public ATextRenderActor, public IEndNaviMapDataProviderInterface {
    GENERATED_BODY()
public:
    AEndTextRenderActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

