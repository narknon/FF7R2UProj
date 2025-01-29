#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndStaticMeshSet.generated.h"

class UStaticMesh;

UCLASS(Blueprintable, MinimalAPI)
class UEndStaticMeshSet : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UStaticMesh* BaseStaticMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UStaticMesh*> OtherStaticMeshs;
    
    UEndStaticMeshSet();

};

