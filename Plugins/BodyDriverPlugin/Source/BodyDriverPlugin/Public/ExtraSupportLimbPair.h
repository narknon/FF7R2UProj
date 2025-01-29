#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExtraSupportLimbPair.generated.h"

USTRUCT(BlueprintType)
struct FExtraSupportLimbPair {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Effector1BoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Effector1LocalPointingDir;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Effector1LocalUpDir;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Effector2BoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Effector2LocalPointingDir;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Effector2LocalUpDir;
    
    BODYDRIVERPLUGIN_API FExtraSupportLimbPair();
};

