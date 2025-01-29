#pragma once
#include "CoreMinimal.h"
#include "EndNavSwitchingVolume.h"
#include "EndNavBlockingModifierVolume.generated.h"

class UEndAerialIgnoreComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndNavBlockingModifierVolume : public AEndNavSwitchingVolume {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IsFirstStart;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndAerialIgnoreComponent* AerialIgnoreComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool CanEverAerial;
    
public:
    AEndNavBlockingModifierVolume(const FObjectInitializer& ObjectInitializer);

};

