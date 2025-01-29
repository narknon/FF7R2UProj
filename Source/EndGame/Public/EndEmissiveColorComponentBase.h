#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndAnimComponentInterface.h"
#include "EndEmissiveColorComponentBase.generated.h"

class ULightComponent;
class UMeshComponent;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndEmissiveColorComponentBase : public UActorComponent, public IEndAnimComponentInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UMeshComponent*> Meshes;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<ULightComponent*> Lights;
    
public:
    UEndEmissiveColorComponentBase(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

