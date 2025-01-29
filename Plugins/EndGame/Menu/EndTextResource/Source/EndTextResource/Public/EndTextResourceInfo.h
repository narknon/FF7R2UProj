#pragma once
#include "CoreMinimal.h"
#include "EndTextResourceInfo.generated.h"

USTRUCT(BlueprintType)
struct ENDTEXTRESOURCE_API FEndTextResourceInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Text;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FString> MetaData;
    
    FEndTextResourceInfo();
};

