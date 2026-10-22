#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RebirthPreviewCameraLibrary.generated.h"

/** Test-host-only camera preparation; no scene or asset packages are saved. */
UCLASS()
class REBIRTHMATERIALPREVIEW_API URebirthPreviewCameraLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Rebirth|Diagnostics", meta = (DevelopmentOnly))
    static FString ConfigureOwnedPreviewCamera();

    /** Render one stable-camera temporal frame in the explicitly owned host. */
    UFUNCTION(BlueprintCallable, Category = "Rebirth|Diagnostics", meta = (DevelopmentOnly))
    static FString WarmOwnedPreviewViewportFrame(float DeltaSeconds);
};
