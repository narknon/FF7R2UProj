#pragma once
#include "CoreMinimal.h"
#include "NavModifierVolume.h"
#include "EndNavMeshIgnoreBrushVolume.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class AEndNavMeshIgnoreBrushVolume : public ANavModifierVolume {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLevelBounds;
    
public:
    AEndNavMeshIgnoreBrushVolume(const FObjectInitializer& ObjectInitializer);

};

