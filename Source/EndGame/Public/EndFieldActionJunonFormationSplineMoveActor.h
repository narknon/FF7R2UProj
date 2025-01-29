#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldSplineActor.h"
#include "EndFieldActionJunonFormationSplineMoveActor.generated.h"

class UEndFieldActionSplineComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndFieldActionJunonFormationSplineMoveActor : public AEndFieldSplineActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionSplineComponent* SplineComponent;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FTransform> SplineLinePoints;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FTransform> Formation00LinePoints;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FTransform> Formation01LinePoints;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FTransform> Formation02LinePoints;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FTransform> Formation03LinePoints;
    
    AEndFieldActionJunonFormationSplineMoveActor(const FObjectInitializer& ObjectInitializer);

};

