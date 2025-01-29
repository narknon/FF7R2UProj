#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EEndStreamLevelCollisionType.h"
#include "EndStreamingTrigger.generated.h"

class UShapeComponent;
class UWorld;

UCLASS(Abstract, Blueprintable)
class AEndStreamingTrigger : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndStreamLevelCollisionType CollisionType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSoftObjectPtr<UWorld>> StreamingLevels;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UShapeComponent* CollisionComponent;
    
public:
    AEndStreamingTrigger(const FObjectInitializer& ObjectInitializer);

};

