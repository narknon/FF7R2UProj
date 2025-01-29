#pragma once
#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "EndSmoothTerrainCollisionComponent.generated.h"

class UBodySetup;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndSmoothTerrainCollisionComponent : public UPrimitiveComponent {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodySetup* BodySetup;
    
public:
    UEndSmoothTerrainCollisionComponent(const FObjectInitializer& ObjectInitializer);

};

