#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndAssetSoftActor.generated.h"

class UObject;

UCLASS(Blueprintable)
class ENDGAME_API AEndAssetSoftActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSoftObjectPtr<UObject>> AssetUserData;
    
    AEndAssetSoftActor(const FObjectInitializer& ObjectInitializer);

};

