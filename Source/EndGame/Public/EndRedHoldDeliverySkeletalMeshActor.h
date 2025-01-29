#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndSkeletalMeshActor.h"
#include "EndRedHoldDeliverySkeletalMeshActor.generated.h"

class UObject;

UCLASS(Blueprintable)
class ENDGAME_API AEndRedHoldDeliverySkeletalMeshActor : public AEndSkeletalMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform IconTransform;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UObject*> RedAssetUserData;
    
    AEndRedHoldDeliverySkeletalMeshActor(const FObjectInitializer& ObjectInitializer);

};

