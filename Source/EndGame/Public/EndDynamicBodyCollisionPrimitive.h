#pragma once
#include "CoreMinimal.h"
#include "EndBodyCollisionPrimitive.h"
#include "EndDynamicBodyCollisionPrimitive.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndDynamicBodyCollisionPrimitive : public UEndBodyCollisionPrimitive {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    float PushSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TSet<FName> IgnoreActorNames;
    
public:
    UEndDynamicBodyCollisionPrimitive(const FObjectInitializer& ObjectInitializer);

};

