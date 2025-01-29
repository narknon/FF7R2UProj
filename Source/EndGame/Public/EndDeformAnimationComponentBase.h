#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndAnimComponentInterface.h"
#include "EndDeformAnimationComponentBase.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndDeformAnimationComponentBase : public UActorComponent, public IEndAnimComponentInterface {
    GENERATED_BODY()
public:
    UEndDeformAnimationComponentBase(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

