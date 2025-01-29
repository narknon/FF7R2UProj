#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "EndEnemyTargetPoint.generated.h"

UCLASS(Blueprintable)
class AEndEnemyTargetPoint : public ATargetPoint {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString BattleCharaSpecName;
    
    AEndEnemyTargetPoint(const FObjectInitializer& ObjectInitializer);

};

