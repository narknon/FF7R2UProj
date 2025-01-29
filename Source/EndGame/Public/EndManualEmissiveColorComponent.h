#pragma once
#include "CoreMinimal.h"
#include "EndEmissiveColorComponentBase.h"
#include "EndEmissiveColorDefaultOnlyMaterialSettings.h"
#include "EndManualEmissiveColorComponent.generated.h"

class USQEXSEADSound;
class USoundAttenuation;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndManualEmissiveColorComponent : public UEndEmissiveColorComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndEmissiveColorDefaultOnlyMaterialSettings MaterialSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* Sound;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SoundLabel;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundAttenuation* Attenuation;
    
    UEndManualEmissiveColorComponent(const FObjectInitializer& ObjectInitializer);

};

