#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RebirthAnimationMotionDiagnosticsLibrary.generated.h"

class UAnimSequence;

/** Editor-only, bounded diagnostics. Never saves or publishes an animation package. */
UCLASS()
class REBIRTHMATERIALPREVIEW_API URebirthAnimationMotionDiagnosticsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Decode the genuine cooked source and converted output through their native ACL codecs.
	 * Also compress/decode a transient source-skeleton loopback, independently reconstruct
	 * same-name parent-compatible target poses, and compare extracted root motion.
	 * Accepts the converter's empty-override, unit-bind-scale MVP only. JSON distinguishes
	 * codec loopback evidence from mapped output validation; neither proves game playback.
	 */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Animation", meta = (DevelopmentOnly))
	static FString ValidateConvertedMotion(UAnimSequence* SourceAnimation,
		UAnimSequence* ConvertedAnimation, float RootTranslationScale);
};
