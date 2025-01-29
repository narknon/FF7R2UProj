#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndCinemaDirectionalLightOverrideActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndCinemaDirectionalLightOverrideActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName PlacedLevel;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> AccessorIds;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    bool bCascadeDistanceEnabled;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    float CascadeDistance0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    float CascadeDistance1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    bool bVisibilityEnabled;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    bool bVisibility;
    
    AEndCinemaDirectionalLightOverrideActor(const FObjectInitializer& ObjectInitializer);

};

