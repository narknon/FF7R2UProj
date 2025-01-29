#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrassGridOctTreeNode.h"
#include "EndGrassOffsetGrid.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndGrassOffsetGrid : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float UnitLength;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 GridNumX;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 GridNumY;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 GridNumZ;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FGrassGridOctTreeNode> InfoTreeNodes_;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 TreeLevel_;
    
    AEndGrassOffsetGrid(const FObjectInitializer& ObjectInitializer);

};

