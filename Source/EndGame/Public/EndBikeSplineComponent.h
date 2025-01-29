#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndBikeSplineJumpAreaData.h"
#include "EndBikeSplineMetaData.h"
#include "EndBikeSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndBikeSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBikeSplineMetaData> SplineMetadata;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBikeSplineJumpAreaData> SplineJumpAreaData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EnemySlideMoveLimitWidth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BuggyMaxSlideLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BuggyEnableInputSlideLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BuggyNoHitSlideLengthBySpecifyPlayerMoveLine;
    
public:
    UEndBikeSplineComponent(const FObjectInitializer& ObjectInitializer);

};

