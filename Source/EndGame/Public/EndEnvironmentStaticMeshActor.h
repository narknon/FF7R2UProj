#pragma once
#include "CoreMinimal.h"
#include "NavPriorRegistInfo.h"
#include "EndStaticMeshActorBase.h"
#include "Templates/SubclassOf.h"
#include "EndEnvironmentStaticMeshActor.generated.h"

class UNavArea;

UCLASS(Blueprintable)
class ENDGAME_API AEndEnvironmentStaticMeshActor : public AEndStaticMeshActorBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAlwaysHiddenActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCanSkillCameraDitherFade;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDrawPauseNavigation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UNavArea> AreaClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverwriteNearFadeDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverwriteNearFadeDistanceOnBattle;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNavPriorRegistInfo NavPriorInfo;
    
public:
    AEndEnvironmentStaticMeshActor(const FObjectInitializer& ObjectInitializer);

};

