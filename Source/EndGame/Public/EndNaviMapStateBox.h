#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EEndNaviMapLayer.h"
#include "EEndNaviMapOpenGroup.h"
#include "EEndNaviMapVisitGroup.h"
#include "EEndSceneNaviMapState.h"
#include "EndNaviMapStateBox.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndNaviMapStateBox : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LocationId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName NaviMapId;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNaviMapLayer LayerNumber;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNaviMapOpenGroup OpenGroupNumber;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNaviMapVisitGroup VisitGroupNumber;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndSceneNaviMapState TargetState;
    
    AEndNaviMapStateBox(const FObjectInitializer& ObjectInitializer);

};

