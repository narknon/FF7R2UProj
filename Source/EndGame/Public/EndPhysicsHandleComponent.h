#pragma once
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "EndPhysicsHandleComponent.generated.h"

class USceneComponent;

UCLASS(Blueprintable, CollapseCategories, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndPhysicsHandleComponent : public UPhysicsHandleComponent {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USceneComponent* TargetScene;
    
public:
    UEndPhysicsHandleComponent(const FObjectInitializer& ObjectInitializer);

};

