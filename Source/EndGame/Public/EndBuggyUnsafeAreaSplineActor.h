#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "EndBuggyUnsafeAreaSplineActor.generated.h"

class UEndBuggyUnsafeAreaSplineComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndBuggyUnsafeAreaSplineActor : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBuggyUnsafeAreaSplineComponent* SplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> WarpPointList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bHideBuggyAfterGetOff;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableHeightLimit;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval HeightLimitRange;
    
public:
    AEndBuggyUnsafeAreaSplineActor(const FObjectInitializer& ObjectInitializer);

};

