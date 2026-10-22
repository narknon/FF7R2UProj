#pragma once

#include "CoreMinimal.h"

class UMaterialInterface;

namespace RebirthMaterialPreviewSafety
{
	struct FResult
	{
		bool bCanRender = false;
		bool bUsesCookedChain = false;
		bool bParentChainValid = false;
		bool bHasInvalidBlendMode = false;
		bool bHasUnsupportedRenderState = false;
		FString Reason;
	};

	/** Inspect already-loaded objects/resources. Does not load, compile, or create RHI shaders. */
	FResult Evaluate(UMaterialInterface* Material);
	bool CanRender(UMaterialInterface* Material, bool& OutUsesCookedChain, FString& OutReason);

	/** Ordinary uncooked materials retain native compilation/thumbnail behavior; invalid blend values never render. */
	bool CanRenderNativeThumbnail(UMaterialInterface* Material, FString& OutReason);
}
