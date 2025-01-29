#pragma once
#include "CoreMinimal.h"
#include "SQEX_BonamikPresetWindSettings_v2.generated.h"

class USQEX_BonamikWindDesc_v2;

USTRUCT(BlueprintType)
struct BONAMIKRT_API FSQEX_BonamikPresetWindSettings_v2 {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_PresetName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEX_BonamikWindDesc_v2* m_WindDesc;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> m_TargetGroups;
    
    FSQEX_BonamikPresetWindSettings_v2();
};

