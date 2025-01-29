#pragma once
#include "CoreMinimal.h"
#include "EndEmissiveColorComponentBase.h"
#include "EndPresetEmissiveColorComponent.generated.h"

class UEndEmissiveColorPreset;
class USQEXSEADSound;
class USoundAttenuation;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndPresetEmissiveColorComponent : public UEndEmissiveColorComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndEmissiveColorPreset* EmissiveColorPreset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* Sound;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SoundLabel;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundAttenuation* Attenuation;
    
    UEndPresetEmissiveColorComponent(const FObjectInitializer& ObjectInitializer);

};

