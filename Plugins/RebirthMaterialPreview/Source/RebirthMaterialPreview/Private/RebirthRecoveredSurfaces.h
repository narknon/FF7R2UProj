#pragma once

class UObject;
class UMaterialInterface;
class UMaterialInstance;
struct FStaticParameterSet;
struct FMaterialInstanceBasePropertyOverrides;

/**
 * In-game shading for RM_Surface materials in the editor.
 *
 * Neither the retail RM_Surface (cooked: Square Enix's frozen shader maps only) nor an editable stand-in graph renders
 * the way the game does. The recovered family masters under /Game/RebirthCompatibility/EditorPreview (StandardWide,
 * StandardWideDetail, CoverageWide, FabricWide, SkinDynamic, HairWide, EyeMigration) contain the retail surface code
 * recovered from the game's shaders plus the renderer adapters for skin, fabric, hair and eye lighting.
 *
 * Editor only, in memory only. Each instance that owns an RM_Surface permutation is pointed at a transient copy of the
 * family master its effective static switches select; the masters keep RM_Surface defaults and declare every RM_Surface
 * parameter and static switch, so the Material Instance Editor keeps all overrides and the retail Coverage_ switch drives
 * the recovered stochastic coverage.
 *  - Cooked instances (which cannot compile a permutation here) get a per-instance transient bridge carrying their
 *    switches' effect, base property overrides and inherited parameter values; their own switches are cleared in memory.
 *  - Editable direct children of RM_Surface keep everything; only their parent changes. Saving one (or a copy of one)
 *    writes RM_Surface back as its parent and the preview is re-applied after the save.
 * Commandlets (cook, Alpakit) never see any of it. Rebirth.RecoveredSurfaces 0 turns it off;
 * Rebirth.RecoveredSurfaces.Restore undoes it; Rebirth.RecoveredSurfaces.Status lists families and shader state.
 */
namespace RebirthRecoveredSurfaces
{
	void Startup();
	void Shutdown();

	/**
	 * Applies the recovered shading now to the cooked instances used by Object (a material, skeletal mesh or static
	 * mesh) and to anything already queued. Game thread, outside rendering; used right before a preview opens so it
	 * starts on the recovered chain instead of waiting for the next tick.
	 */
	void ApplyNow(UObject* Object);

	/** True when Material's parent chain currently renders through a recovered family master. */
	bool IsRecovered(const UMaterialInterface* Material);

	/** True when Material is the cooked retail RM_Surface base material. */
	bool IsRetailSurfaceBase(const UMaterialInterface* Material);

	/**
	 * The parent, static parameters and base property overrides a redirected cooked instance was loaded with; false
	 * when Instance was never redirected. Used when converting a cooked instance into an editable asset.
	 */
	bool GetOriginalState(const UMaterialInstance* Instance, UMaterialInterface*& OutParent, FStaticParameterSet& OutStaticParameters,
		FMaterialInstanceBasePropertyOverrides& OutBasePropertyOverrides);
}
