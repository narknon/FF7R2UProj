#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndNavGridData.h"
#include "EndNavGridActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndNavGridActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString BaseLocationId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndNavGridData> NavGrids;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 Priority;
    
    AEndNavGridActor(const FObjectInitializer& ObjectInitializer);

};

