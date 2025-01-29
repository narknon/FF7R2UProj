#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndStaticMeshActorBase.h"
#include "EndRedHoldDeliveryStaticMeshActor.generated.h"

class UObject;
class USoundBase;

UCLASS(Blueprintable)
class ENDGAME_API AEndRedHoldDeliveryStaticMeshActor : public AEndStaticMeshActorBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UObject*> RedAssetUserData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bHoldObjectMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform HoldOffsetTransform;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform ItemRootOffsetTransform;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RedCatchBlendRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* HoldSound_Drop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* HoldSound_Hold;
    
    AEndRedHoldDeliveryStaticMeshActor(const FObjectInitializer& ObjectInitializer);

};

