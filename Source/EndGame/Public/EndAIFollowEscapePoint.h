#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndAIFollowEscapePoint.generated.h"

UCLASS(Abstract, Blueprintable)
class AEndAIFollowEscapePoint : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OwnerTerritoryId;
    
public:
    AEndAIFollowEscapePoint(const FObjectInitializer& ObjectInitializer);

};

