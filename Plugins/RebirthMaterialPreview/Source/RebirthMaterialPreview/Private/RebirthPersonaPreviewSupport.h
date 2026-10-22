#pragma once

#include "CoreMinimal.h"
#include "Animation/DebugSkelMeshComponent.h"
#include "RebirthBonamikPreviewSession.h"
#include "RebirthPersonaPreviewSupport.generated.h"

// Editor-only, transient Persona component. Native animation, cloth and physics
// behavior is inherited. No game mesh, material slot or cooked package is edited.
//
// Bonamik: when the previewed mesh carries Bonamik data (SQEX_KBD_AssetUserData -> BonamikDataList), the custom
// preview solver runs on top of the animated pose every frame (hair, cloth, accessories follow the animation).
// The simulated bones are written only into this component's freshly evaluated component-space pose, right before
// it is published for rendering; the animation itself, the mesh and the BNM assets are never changed.
UCLASS(Transient)
class URebirthPersonaPreviewMeshComponent : public UDebugSkelMeshComponent
{
    GENERATED_BODY()

public:
    URebirthPersonaPreviewMeshComponent(const FObjectInitializer& ObjectInitializer);
    virtual void SetSkeletalMesh(USkeletalMesh* NewMesh, bool bReinitPose = true) override;
    virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;
    virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;
    virtual void BeginDestroy() override;
    virtual void FinalizeBoneTransform() override;

    /** One line for the toolbar tooltip: what the Bonamik preview is doing for this mesh. */
    FText GetBonamikStatusText() const;
    bool HasBonamik() const { return BonamikSessions.Num() > 0; }

    /** Re-resolves the preview materials on the next tick and keeps retrying while their shaders compile. */
    void RequestMaterialRefresh();

private:
    void ResolvePreviewMaterials(USkeletalMesh* Mesh);
    void InitializeBonamik(USkeletalMesh* Mesh);
    void ClearBonamik();
    void ApplyBonamik();

    UPROPERTY(Transient)
    TArray<UMaterialInterface*> SafePreviewMaterials;

    UPROPERTY(Transient)
    UMaterialInterface* SafeFallbackMaterial;

    bool bProtectMaterials = false;
    bool bRetryMaterials = false;
    double RetryDeadline = 0.0;
    double NextRetryTime = 0.0;

    TArray<TUniquePtr<FRebirthBonamikPreviewSession>> BonamikSessions;
    TWeakObjectPtr<USkeletalMesh> BonamikMesh;
    FString BonamikStatus;
    float PendingBonamikSeconds = 0.0f;
    int32 BonamikResetSerial = 0;
    int32 BonamikFailedFrames = 0;
    bool bBonamikRunning = false;
};

namespace RebirthPersonaPreviewSupport
{
    // Call once from the editor module's StartupModule/ShutdownModule.
    void Register();
    void Unregister();

    /** Global switch shared by every Persona preview (console: Rebirth.Bonamik.Persona 0/1). */
    bool IsBonamikEnabled();
    void SetBonamikEnabled(bool bEnabled);
    /** Restarts every Persona Bonamik simulation from the current animated pose. */
    void ResetBonamik();
    int32 GetBonamikResetSerial();

    /** Every Persona preview re-resolves its materials (cooked materials just became renderable, or stopped being). */
    void RefreshPreviewMaterials();
}
