#pragma once
#include "CoreMinimal.h"
#include "EndTriggerBox.h"
#include "EndBlackCloakAssetLoadActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndBlackCloakAssetLoadActor : public AEndTriggerBox {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AssetPackerID;
    
    AEndBlackCloakAssetLoadActor(const FObjectInitializer& ObjectInitializer);

};

