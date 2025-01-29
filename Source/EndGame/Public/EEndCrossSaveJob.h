#pragma once
#include "CoreMinimal.h"
#include "EEndCrossSaveJob.generated.h"

UENUM(BlueprintType)
enum class EEndCrossSaveJob : uint8 {
    None,
    Read,
    Upload,
    Download,
    Write,
    ReadUpload,
    DownloadWrite,
};

