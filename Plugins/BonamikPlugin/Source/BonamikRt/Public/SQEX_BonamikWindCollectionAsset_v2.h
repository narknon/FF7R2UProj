#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SQEX_BonamikPresetWindSettings_v2.h"
#include "SQEX_BonamikWindCollectionAsset_v2.generated.h"

UCLASS(Blueprintable)
class BONAMIKRT_API USQEX_BonamikWindCollectionAsset_v2 : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSQEX_BonamikPresetWindSettings_v2> m_BonamikPresetWindSettings;
    
    USQEX_BonamikWindCollectionAsset_v2();

};

