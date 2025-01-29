#pragma once
#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "SQEX_BonamikPresetWindSettings_v2.h"
#include "SQEX_WorldSettings_v2.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class ASQEX_WorldSettings_v2 : public AWorldSettings {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEX_BonamikPresetWindSettings_v2 m_BonamikPresetWindSettings[10];
    
    ASQEX_WorldSettings_v2(const FObjectInitializer& ObjectInitializer);

};

