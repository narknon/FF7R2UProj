#pragma once
#include "CoreMinimal.h"
#include "EndCameraSequenceObjectPath.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCameraSequenceObjectPath {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AssetPathName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString SubStringPath;
    
    FEndCameraSequenceObjectPath();
};

