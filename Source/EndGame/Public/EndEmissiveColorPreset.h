#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndEmissiveColorDefaultOnlyMaterialSettings.h"
#include "EndEmissiveColorPreset.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndEmissiveColorPreset : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndEmissiveColorDefaultOnlyMaterialSettings MaterialSettings;
    
    UEndEmissiveColorPreset();

};

