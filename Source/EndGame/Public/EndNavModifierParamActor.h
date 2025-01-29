#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AerialPortalEdge.h"
#include "CreateAStarPointData.h"
#include "EndNavModifierInfo.h"
#include "EndNavModifierParamActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndNavModifierParamActor : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndNavModifierInfo> ModifierInfoArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FCreateAStarPointData> CreateAerialPointList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FCreateAStarPointData> CreateWallPointList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FAerialPortalEdge> CreateAerialEdgeList;
    
public:
    AEndNavModifierParamActor(const FObjectInitializer& ObjectInitializer);

};

