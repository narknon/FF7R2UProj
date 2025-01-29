#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndAssetClassActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndAssetClassActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UClass*> AssetUserData;
    
    AEndAssetClassActor(const FObjectInitializer& ObjectInitializer);

};

