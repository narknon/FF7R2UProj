#pragma once
#include "CoreMinimal.h"
#include "CustomWindSettings.h"
#include "SQEX_BonamikWind_Actor_v2.h"
#include "SQEX_BonamikCustomWind_Actor_v2.generated.h"

UCLASS(Blueprintable)
class BONAMIKRT_API ADEPRECATED_SQEX_BonamikCustomWind_Actor_v2 : public ADEPRECATED_SQEX_BonamikWind_Actor_v2 {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FCustomWindSettings m_WindSetting;
    
    ADEPRECATED_SQEX_BonamikCustomWind_Actor_v2(const FObjectInitializer& ObjectInitializer);

};

