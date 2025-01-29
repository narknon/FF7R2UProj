#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EndGroundFillMesh.h"
#include "EndGroundFillType.generated.h"

UCLASS(Blueprintable)
class UEndGroundFillType : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndGroundFillMesh> Meshes;
    
    UEndGroundFillType();

};

