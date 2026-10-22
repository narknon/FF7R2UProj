#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RebirthMaterialPreviewPreflight.generated.h"

class UMaterialInterface;

namespace RebirthMaterialPreviewPreflight
{
	struct REBIRTHMATERIALPREVIEW_API FResult
	{
		bool bAllowed = false;
		bool bContainsCookedMaterial = false;
		FString Reason;
		FString Json;
	};

	/** Observes existing game-thread resources only; never loads, compiles, or creates RHI shaders. */
	REBIRTHMATERIALPREVIEW_API FResult Evaluate(UMaterialInterface* Material);
}

UCLASS()
class REBIRTHMATERIALPREVIEW_API URebirthMaterialPreviewPreflightLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Returns JSON describing whether current material/parent resources pass conservative preview gates. */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Diagnostics")
	static FString GetMaterialRuntimePreviewPreflight(UMaterialInterface* Material);
};
