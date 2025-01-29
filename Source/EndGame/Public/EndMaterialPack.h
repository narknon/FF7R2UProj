#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndMaterialPack.generated.h"

class UMaterialInterface;

UCLASS(Blueprintable)
class ENDGAME_API UEndMaterialPack : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, UMaterialInterface*> MaterialAssets;
    
    UEndMaterialPack();

};

