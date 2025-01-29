#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndChocoboGlideGimmickSplineMoveParam.h"
#include "EndChocoboGlideGimmickSplineActorBase.generated.h"

class UEndChocoboGlideGimmickSplineComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndChocoboGlideGimmickSplineActorBase : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndChocoboGlideGimmickSplineComponent* GimmickSplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndChocoboGlideGimmickSplineMoveParam MoveParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableMove;
    
public:
    AEndChocoboGlideGimmickSplineActorBase(const FObjectInitializer& ObjectInitializer);

};

