#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "SQEX_BonamikWind_Actor_v2.generated.h"

class UDEPRECATED_SQEX_BonamikWind_Component_v2;

UCLASS(Blueprintable, Deprecated, NotPlaceable)
class BONAMIKRT_API ADEPRECATED_SQEX_BonamikWind_Actor_v2 : public AInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UDEPRECATED_SQEX_BonamikWind_Component_v2* m_BonamikWind_Component;
    
    ADEPRECATED_SQEX_BonamikWind_Actor_v2(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetWindScale(float Value);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetWindScale() const;
    
    UFUNCTION(BlueprintCallable)
    void Enable(bool Value);
    
};

