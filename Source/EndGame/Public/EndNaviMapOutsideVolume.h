#pragma once
#include "CoreMinimal.h"
#include "EndSplineBrushVolume.h"
#include "EndNaviMapOutsideVolume.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class AEndNaviMapOutsideVolume : public AEndSplineBrushVolume {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> EnablePatternNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> DisablePatternNames;
    
    AEndNaviMapOutsideVolume(const FObjectInitializer& ObjectInitializer);

};

