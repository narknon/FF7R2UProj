#pragma once

#include "CoreMinimal.h"
#include "ThumbnailRendering/DefaultSizedThumbnailRenderer.h"
#include "RebirthSafeSkeletalMeshThumbnailRenderer.generated.h"

/** Checks every original material before the native renderer creates a mesh scene. */
UCLASS()
class REBIRTHMATERIALPREVIEW_API URebirthSafeSkeletalMeshThumbnailRenderer : public UDefaultSizedThumbnailRenderer
{
	GENERATED_BODY()

public:
	URebirthSafeSkeletalMeshThumbnailRenderer(const FObjectInitializer& ObjectInitializer);

	/** Configure the CDO before registration; each instance retains its own native delegate. */
	bool SetDelegateRendererClass(UClass* RendererClass);
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
