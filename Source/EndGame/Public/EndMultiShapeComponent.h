#pragma once
#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "EndCollisionShapeUnit.h"
#include "EndMultiShapeComponent.generated.h"

class UBodySetup;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndMultiShapeComponent : public UPrimitiveComponent {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCollisionShapeUnit> CollisionShapes;
    
    UPROPERTY(BlueprintReadWrite, DuplicateTransient, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UBodySetup* ShapeBodySetup;
    
public:
    UEndMultiShapeComponent(const FObjectInitializer& ObjectInitializer);

};

