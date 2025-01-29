#pragma once
#include "CoreMinimal.h"
#include "EndTargetPoint.h"
#include "EndFieldBGMLocationPoint.generated.h"

UCLASS(Blueprintable)
class AEndFieldBGMLocationPoint : public AEndTargetPoint {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSet<FName> TargetBGM;
    
    AEndFieldBGMLocationPoint(const FObjectInitializer& ObjectInitializer);

};

