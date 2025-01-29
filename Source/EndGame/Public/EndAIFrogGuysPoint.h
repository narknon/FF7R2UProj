#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "EEndAIFrogGuysType.h"
#include "EndAIFrogGuysPoint.generated.h"

UCLASS(Blueprintable)
class AEndAIFrogGuysPoint : public ATargetPoint {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIFrogGuysType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Range;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BottomOffset;
    
public:
    AEndAIFrogGuysPoint(const FObjectInitializer& ObjectInitializer);

};

