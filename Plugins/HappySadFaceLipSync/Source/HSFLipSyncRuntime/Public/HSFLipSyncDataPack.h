#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HSFLipSyncData.h"
#include "HSFLipSyncDataPack.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UHSFLipSyncDataPack : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FHSFLipSyncData> Data;
    
    UHSFLipSyncDataPack();

};

