#pragma once

#include "CoreMinimal.h"
#include "ThumbnailRendering/DefaultSizedThumbnailRenderer.h"
#include "RebirthSafeMaterialThumbnailRenderer.generated.h"

/** Composes an existing renderer; does not inherit from the unexported material renderer. */
UCLASS()
class REBIRTHMATERIALPREVIEW_API URebirthSafeMaterialThumbnailRenderer : public UDefaultSizedThumbnailRenderer
{
	GENERATED_BODY()

public:
	URebirthSafeMaterialThumbnailRenderer(const FObjectInitializer& ObjectInitializer);

	/** Set on this class's CDO before RegisterCustomRenderer; each instance lazily creates its own delegate. */
	bool SetDelegateRendererClass(UClass* RendererClass);
	/** Optional alternative: retain the exact previously registered renderer instance through a UPROPERTY. */
	bool SetDelegateRenderer(UThumbnailRenderer* Renderer);

	virtual bool CanVisualizeAsset(UObject* Object) override;
	virtual void GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth, uint32& OutHeight) const override;
	virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* Viewport, FCanvas* Canvas, bool bAdditionalViewFamily) override;
	virtual bool AllowsRealtimeThumbnails(UObject* Object) const override;

private:
	UThumbnailRenderer* GetDelegateRenderer();
	bool IsAllowed(UObject* Object, FString& OutReason) const;
	void ReportBlocked(UObject* Object, const FString& Reason);

	UPROPERTY(Transient)
	TSubclassOf<UThumbnailRenderer> DelegateRendererClass;
	UPROPERTY(Transient)
	UThumbnailRenderer* DelegateRenderer;
	TSet<FString> ReportedBlockedAssets;
};
