#pragma once
#include "CoreMinimal.h"
#include "EndAssetClass.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAssetClass {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AssetName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UClass*> AssetUserData;
    
    FEndAssetClass();
};

