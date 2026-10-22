#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RebirthMaterialDiagnosticsLibrary.generated.h"

class UMaterialInterface;
class UMaterial;
class UMaterialInstanceConstant;
class UMaterialExpression;
class UMaterialExpressionComment;

UCLASS()
class REBIRTHMATERIALPREVIEW_API URebirthMaterialDiagnosticsLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Check already-loaded material state without loading, compiling, or submitting it to the renderer. */
    UFUNCTION(BlueprintCallable, Category = "Rebirth|Material Diagnostics")
    static FString GetMaterialPreviewPreflight(UMaterialInterface* Material);

    /** Read actual current-RHI material resources without reconstructing or editing graphs.
     * Optional waiting only finishes compilation jobs which already exist.
     * Python: unreal.RebirthMaterialDiagnosticsLibrary.get_material_diagnostics(material, False)
     */
    UFUNCTION(BlueprintCallable, Category = "Rebirth|Material Diagnostics")
    static FString GetMaterialDiagnostics(UMaterialInterface* Material, bool bWaitForCompilation = false);

    /** A transient instance of Base with the listed static switches on (and Base's blend mode replaced, when BlendMode names
     * one: "BLEND_Masked"), compiled for the current RHI as any edited instance is. For checking a base material's static
     * permutations from a script: get_material_diagnostics(instance, True) then waits for it and lists its compile errors.
     * Python: unreal.RebirthMaterialDiagnosticsLibrary.create_static_permutation(base, ["Color_", "Normal_"], "BLEND_Masked")
     */
    UFUNCTION(BlueprintCallable, Category = "Rebirth|Material Diagnostics")
    static UMaterialInstanceConstant* CreateStaticPermutation(UMaterial* Base, const TArray<FString>& StaticSwitchesOn, const FString& BlendMode);

    /** Sets a material instance asset's own static parameters the way the Material Instance Editor does: the listed
     * static switches (SwitchValues[i] for SwitchNames[i]) and component masks (MaskValues[i] holds the letters that are on,
     * "RG"), all overridden, and its base property overrides (BlendMode "BLEND_Masked", ShadingModel "MSM_DefaultLit",
     * TwoSided 0/1, OpacityMaskClipValue; "" / -1 / a negative clip value leave one as it is), then updates its static
     * permutation (a recompile) and marks it dirty. Returns a JSON receipt: what was set, names the parent chain does not have.
     * Python: unreal.RebirthMaterialDiagnosticsLibrary.set_material_instance_static_parameters(mi, ["Edge"], [True], [], [], "", "", -1, -1.0)
     */
    UFUNCTION(BlueprintCallable, Category = "Rebirth|Material Diagnostics")
    static FString SetMaterialInstanceStaticParameters(UMaterialInstanceConstant* Instance, const TArray<FString>& SwitchNames, const TArray<bool>& SwitchValues,
        const TArray<FString>& MaskNames, const TArray<FString>& MaskValues, const FString& BlendMode, const FString& ShadingModel, int32 TwoSided, float OpacityMaskClipValue);

    /** Connects an expression's output to one of its material's inputs, the input named by its C++ name ("MP_ShadingModel").
     * For the inputs Python's MaterialProperty enum leaves out (UMETA(Hidden): MP_ShadingModel, MP_WorldPositionOffset,
     * MP_CustomizedUVs0, ...). An empty output name is the first output. Returns false when nothing was connected.
     * Python: unreal.RebirthMaterialDiagnosticsLibrary.connect_material_property_by_name(expression, "", "MP_ShadingModel")
     */
    UFUNCTION(BlueprintCallable, Category = "Rebirth|Material Diagnostics")
    static bool ConnectMaterialPropertyByName(UMaterialExpression* FromExpression, const FString& FromOutputName, const FString& PropertyName);

    /** Adds a comment box to a material's graph (the material's EditorComments, which Python can't reach).
     * Python: unreal.RebirthMaterialDiagnosticsLibrary.add_material_comment(material, x, y, width, height, "text")
     */
    UFUNCTION(BlueprintCallable, Category = "Rebirth|Material Diagnostics")
    static UMaterialExpressionComment* AddMaterialComment(UMaterial* Material, int32 X, int32 Y, int32 Width, int32 Height, const FString& Text);

    /** Removes every comment box from a material's graph. */
    UFUNCTION(BlueprintCallable, Category = "Rebirth|Material Diagnostics")
    static void ClearMaterialComments(UMaterial* Material);

    /** Inspect a loaded object without creating its native asset editor, compiling
     * Blueprint graphs, constructing gameplay instances, or following references.
     */
    UFUNCTION(BlueprintCallable, Category = "Rebirth|Cooked Asset Diagnostics")
    static FString GetAssetDiagnostics(UObject* Asset);

    /** Explicitly load an asset and inspect it. A phase JSON is flushed under
     * Saved/RebirthMaterialPreview/Diagnostics before native LoadObject starts.
     * A loader failure can still crash the process; this is diagnostic evidence,
     * not a crash recovery mechanism or gameplay execution test.
     */
    UFUNCTION(BlueprintCallable, Category = "Rebirth|Cooked Asset Diagnostics")
    static FString LoadAssetDiagnostics(const FString& ObjectPath);

    /** Draw the active level-editor viewport and synchronously save its actual
     * pixels to an absolute PNG filename. Requires an initialized rendering
     * editor on the game thread; it does not create a SceneCapture actor or
     * change scene assets. Python returns a JSON receipt, including failures.
     */
    UFUNCTION(BlueprintCallable, Category = "Rebirth|Preview Capture")
    static FString CaptureEditorViewportImage(const FString& Filename, bool bUsePilotedCameraSettings = false);
};
