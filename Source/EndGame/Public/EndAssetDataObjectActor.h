#pragma once
#include "CoreMinimal.h"
#include "EndAssetActor.h"
#include "EndAssetDataObjectActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndAssetDataObjectActor : public AEndAssetActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString LocationId;
    
    AEndAssetDataObjectActor(const FObjectInitializer& ObjectInitializer);

};

