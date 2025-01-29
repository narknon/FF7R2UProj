#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndAssetSaveData.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndAssetSaveData : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Name;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString ParentLocation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> SaveData;
    
    UEndAssetSaveData();

};

