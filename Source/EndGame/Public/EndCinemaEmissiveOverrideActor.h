#pragma once
#include "CoreMinimal.h"
#include "EndCinemaPostProcessActor.h"
#include "EndCinemaEmissiveOverrideActor.generated.h"

class UEndCinemaEmissiveOverrideComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndCinemaEmissiveOverrideActor : public AEndCinemaPostProcessActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCinemaEmissiveOverrideComponent* ControllerComponent;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> Actors;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLightVisibility;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverrideSeamlessInTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverrideSeamlessOutTime;
    
    AEndCinemaEmissiveOverrideActor(const FObjectInitializer& ObjectInitializer);

};

