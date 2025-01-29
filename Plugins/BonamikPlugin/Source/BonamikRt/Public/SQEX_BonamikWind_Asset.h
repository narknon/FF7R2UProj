#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SQEX_BonamikWind_Desc.h"
#include "SQEX_BonamikWind_Asset.generated.h"

UCLASS(Blueprintable)
class BONAMIKRT_API USQEX_BonamikWind_Asset : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSQEX_BonamikWind_Desc> mWinds;
    
    USQEX_BonamikWind_Asset();

};

