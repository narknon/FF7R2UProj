#pragma once
#include "CoreMinimal.h"
#include "EndMenuColorCorrectionSelection.generated.h"

class UVolumeTexture;

USTRUCT(BlueprintType)
struct FEndMenuColorCorrectionSelection {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UVolumeTexture* LookUpTable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString NameTextID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ResidentWorkName;
    
    ENDGAME_API FEndMenuColorCorrectionSelection();
};

