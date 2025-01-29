#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EndDolphinJumpOceanFloaterComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndDolphinJumpOceanFloaterComponent : public USceneComponent {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool EnableDisplacement;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool EnableRotation;
    
public:
    UEndDolphinJumpOceanFloaterComponent(const FObjectInitializer& ObjectInitializer);

};

