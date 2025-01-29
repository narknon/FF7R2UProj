#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SQEX_BonamikPresetWindInstance.h"
#include "SQEX_BonamikWindController_v2.generated.h"

class USQEX_BonamikWind_v2;
class UWorld;

USTRUCT(BlueprintType)
struct BONAMIKRT_API FSQEX_BonamikWindController_v2 {
    GENERATED_BODY()
public:
private:
    UPROPERTY(EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FSQEX_BonamikPresetWindInstance m_PresetWind[10];
    
    UPROPERTY(EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<TWeakObjectPtr<USQEX_BonamikWind_v2>> m_WindSources;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FVector m_CurrentGlobalWindForce;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_GlobalWindScale;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<UWorld> RefWorld;
    
public:
    FSQEX_BonamikWindController_v2();
};

