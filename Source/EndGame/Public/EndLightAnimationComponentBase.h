#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndAnimComponentInterface.h"
#include "EndLightAnimationComponentBase.generated.h"

class ULightComponent;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndLightAnimationComponentBase : public UActorComponent, public IEndAnimComponentInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetLightNames;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<ULightComponent*> Lights;
    
public:
    UEndLightAnimationComponentBase(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

