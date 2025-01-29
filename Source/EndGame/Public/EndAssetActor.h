#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndAssetActor.generated.h"

class UObject;

UCLASS(Blueprintable)
class ENDGAME_API AEndAssetActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UObject*> AssetUserData;
    
    AEndAssetActor(const FObjectInitializer& ObjectInitializer);

};

