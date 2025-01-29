#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "EndBattleCrystalAppearPoint.generated.h"

UCLASS(Blueprintable)
class AEndBattleCrystalAppearPoint : public ATargetPoint {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName GroupName;
    
    AEndBattleCrystalAppearPoint(const FObjectInitializer& ObjectInitializer);

};

