#pragma once
#include "CoreMinimal.h"
#include "EndCylinderComponent.h"
#include "EndChocoboGlideRingOverlapComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndChocoboGlideRingOverlapComponent : public UEndCylinderComponent {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Point;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName VibrationID;
    
public:
    UEndChocoboGlideRingOverlapComponent(const FObjectInitializer& ObjectInitializer);

};

