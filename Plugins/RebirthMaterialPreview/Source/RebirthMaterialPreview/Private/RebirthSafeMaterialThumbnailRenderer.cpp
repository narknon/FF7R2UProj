#include "RebirthSafeMaterialThumbnailRenderer.h"

#include "Materials/MaterialInterface.h"
#include "RebirthMaterialPreviewSafety.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthMaterialPreviewSafety, Log, All);

URebirthSafeMaterialThumbnailRenderer::URebirthSafeMaterialThumbnailRenderer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), DelegateRenderer(nullptr)
{
}

bool URebirthSafeMaterialThumbnailRenderer::SetDelegateRendererClass(UClass* RendererClass)
{
	if (!RendererClass || !RendererClass->IsChildOf(UThumbnailRenderer::StaticClass()) || RendererClass->IsChildOf(StaticClass()) || RendererClass->HasAnyClassFlags(CLASS_Abstract))
	{
		return false;
	}
	DelegateRendererClass = RendererClass;
	DelegateRenderer = nullptr;
	return true;
}

bool URebirthSafeMaterialThumbnailRenderer::SetDelegateRenderer(UThumbnailRenderer* Renderer)
{
	if (!IsValid(Renderer) || Renderer == this || Renderer->IsA(StaticClass()))
	{
		return false;
	}
	DelegateRenderer = Renderer;
	DelegateRendererClass = Renderer->GetClass();
	return true;
}

UThumbnailRenderer* URebirthSafeMaterialThumbnailRenderer::GetDelegateRenderer()
{
	if (!IsValid(DelegateRenderer) && DelegateRendererClass && !DelegateRendererClass->IsChildOf(StaticClass()))
	{
		DelegateRenderer = NewObject<UThumbnailRenderer>(this, DelegateRendererClass);
	}
	return DelegateRenderer;
}

bool URebirthSafeMaterialThumbnailRenderer::IsAllowed(UObject* Object, FString& OutReason) const
{
	UMaterialInterface* Material = Cast<UMaterialInterface>(Object);
	if (!Material)
	{
		OutReason = TEXT("not_a_material_interface");
		return false;
	}
	return RebirthMaterialPreviewSafety::CanRenderNativeThumbnail(Material, OutReason);
}

bool URebirthSafeMaterialThumbnailRenderer::CanVisualizeAsset(UObject* Object)
{
	FString Reason;
	if (!IsAllowed(Object, Reason))
	{
		ReportBlocked(Object, Reason);
		return false;
	}
	UThumbnailRenderer* Delegate = GetDelegateRenderer();
	return Delegate && Delegate->CanVisualizeAsset(Object);
}

void URebirthSafeMaterialThumbnailRenderer::ReportBlocked(UObject* Object, const FString& Reason)
{
	const FString Asset = IsValid(Object) ? Object->GetPathName() : TEXT("<invalid>");
	if (!ReportedBlockedAssets.Contains(Asset))
	{
		ReportedBlockedAssets.Add(Asset);
		UE_LOG(LogRebirthMaterialPreviewSafety, Warning, TEXT("MaterialThumbnailBlocked asset=%s reason=%s"), *Asset, *Reason);
	}
}

void URebirthSafeMaterialThumbnailRenderer::GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth, uint32& OutHeight) const
{
	FString Reason;
	UThumbnailRenderer* Delegate = IsAllowed(Object, Reason) ? const_cast<URebirthSafeMaterialThumbnailRenderer*>(this)->GetDelegateRenderer() : nullptr;
	if (Delegate)
	{
		Delegate->GetThumbnailSize(Object, Zoom, OutWidth, OutHeight);
	}
	else
	{
		Super::GetThumbnailSize(Object, Zoom, OutWidth, OutHeight);
	}
}

void URebirthSafeMaterialThumbnailRenderer::Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* Viewport, FCanvas* Canvas, bool bAdditionalViewFamily)
{
	FString Reason;
	if (!IsAllowed(Object, Reason))
	{
		ReportBlocked(Object, Reason);
		return;
	}
	if (UThumbnailRenderer* Delegate = GetDelegateRenderer())
	{
		Delegate->Draw(Object, X, Y, Width, Height, Viewport, Canvas, bAdditionalViewFamily);
	}
}

bool URebirthSafeMaterialThumbnailRenderer::AllowsRealtimeThumbnails(UObject* Object) const
{
	FString Reason;
	UThumbnailRenderer* Delegate = IsAllowed(Object, Reason) ? const_cast<URebirthSafeMaterialThumbnailRenderer*>(this)->GetDelegateRenderer() : nullptr;
	return Delegate && Delegate->AllowsRealtimeThumbnails(Object);
}
