#include "SQEX_BonamikWind_Actor_v2.h"
#include "SQEX_BonamikWind_Component_v2.h"

ADEPRECATED_SQEX_BonamikWind_Actor_v2::ADEPRECATED_SQEX_BonamikWind_Actor_v2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UDEPRECATED_SQEX_BonamikWind_Component_v2>(TEXT("SQEX_BonamikWind_Component"));
    this->m_BonamikWind_Component = (UDEPRECATED_SQEX_BonamikWind_Component_v2*)RootComponent;
}

void ADEPRECATED_SQEX_BonamikWind_Actor_v2::SetWindScale(float Value) {
}

float ADEPRECATED_SQEX_BonamikWind_Actor_v2::GetWindScale() const {
    return 0.0f;
}

void ADEPRECATED_SQEX_BonamikWind_Actor_v2::Enable(bool Value) {
}


