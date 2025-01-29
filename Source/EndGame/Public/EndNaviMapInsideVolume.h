#pragma once
#include "CoreMinimal.h"
#include "EndSplineBrushVolume.h"
#include "EndNaviMapInsideVolume.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class AEndNaviMapInsideVolume : public AEndSplineBrushVolume {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> EnablePatternNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> DisablePatternNames;
    
    AEndNaviMapInsideVolume(const FObjectInitializer& ObjectInitializer);

};

