#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RebirthShaderLayoutDiagnosticsLibrary.generated.h"

/** CPU-only comparison of the original retail RM_Surface's saved shader layouts. */
UCLASS()
class REBIRTHMATERIALPREVIEW_API URebirthShaderLayoutDiagnosticsLibrary : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()

public:
	/** Returns classified JSON. Does not load assets, create RHI resources, or change loader acceptance. */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Diagnostics")
	static FString GetRetailShaderLayoutDiagnostics();
};
