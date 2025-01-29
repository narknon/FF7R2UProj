#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndDolphinJumpSplinePhaseData.h"
#include "EndDolphinJumpSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndDolphinJumpSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Width;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float JumpLineDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndDolphinJumpSplinePhaseData> Phases;
    
    UEndDolphinJumpSplineComponent(const FObjectInitializer& ObjectInitializer);

};

