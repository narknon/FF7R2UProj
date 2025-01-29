#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackCloakFootprintBPInfo.h"
#include "BlackCloakFootprintCreationType.h"
#include "BlackCloakFootprintEffectInfo.h"
#include "EndBlackCloakFootprintGroupActor.generated.h"

class USplineComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndBlackCloakFootprintGroupActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    BlackCloakFootprintCreationType _SpawnType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USplineComponent* FootPrintBaseComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackCloakFootprintBPInfo _RightHandBP;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackCloakFootprintBPInfo _LeftHandBP;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackCloakFootprintBPInfo _RightFootBP;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackCloakFootprintBPInfo _LeftFootBP;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float _HorizontalDistBetweenFootPrints;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float _VerticalDistBetweenFootPrints;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float _FootPrintsAngle;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TWeakObjectPtr<AActor>> ChildActors;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AssetPackName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FBlackCloakFootprintEffectInfo> ChildActorDatas;
    
    AEndBlackCloakFootprintGroupActor(const FObjectInitializer& ObjectInitializer);

};

