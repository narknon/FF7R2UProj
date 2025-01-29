#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "SQEX_KBD_OverrideBonamikDataList.h"
#include "SQEX_KBD_AssetUserData.generated.h"

class USQEX_BonamikAsset;
class USQEX_KineDriverData;

UCLASS(Blueprintable, EditInlineNew)
class KBDRT_API USQEX_KBD_AssetUserData : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<USQEX_BonamikAsset*> BonamikDataList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSQEX_KBD_OverrideBonamikDataList> OverrideBonamikDataList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<USQEX_KineDriverData*> KineDriverDataList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<USQEX_KineDriverData*> PostKineDriverDataList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 BonamikDefaultPreRollCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 BonamikCinemaPreRollCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableHighFpsEvaluation;
    
    USQEX_KBD_AssetUserData();

};

