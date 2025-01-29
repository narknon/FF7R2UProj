#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EEndAnimationCurveType.h"
#include "EndEmissiveColorMaterial.h"
#include "EndEmissiveColorSettings.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndEmissiveColorSettings : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndEmissiveColorMaterial> MaterialSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndEmissiveColorMaterial> Materials;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimationCurveType DefaultCurve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DefaultDuration;
    
    UEndEmissiveColorSettings();

};

