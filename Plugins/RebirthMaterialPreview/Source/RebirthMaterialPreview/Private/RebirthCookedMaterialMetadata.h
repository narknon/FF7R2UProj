#pragma once

class UMaterial;
class UMaterialInterface;

/**
 * Cooked base materials (RM_Surface and every other retail UMaterial) load without their editor-only cached parameter
 * data: slider ranges, curve atlases, channel names and channel-mask flags were stripped when the game was cooked,
 * while the runtime parameter lists are intact. Unreal's editor getters (UMaterial::GetScalarParameterSliderMinMax,
 * IsScalarParameterUsedAsAtlasPosition, IsVectorParameterUsedAsChannelMask, GetVectorParameterChannelNames,
 * GetTextureParameterChannelNames) find a parameter in the runtime list and then index the stripped arrays with the
 * same index, so the Material Instance Editor asserts ("Array index out of bounds: 0 from an array of size 0") when it
 * opens any material instance whose parent chain ends in a cooked material.
 *
 * Repair() pads the stripped arrays with neutral values (no slider range, no curve, default channel names, not a
 * channel mask) so every getter stays in range. Nothing is saved; cooked packages are never written and the padding is
 * redone whenever the material loads.
 */
namespace RebirthCookedMaterialMetadata
{
	/** Returns true when Material is cooked and something had to be padded. */
	bool Repair(UMaterial* Material);

	/** Repairs the cooked base material at the end of Material's parent chain (Material may be any instance). */
	void RepairChain(const UMaterialInterface* Material);

	/** Repairs cooked materials already loaded and every one loaded later. Editor only. */
	void Startup();
	void Shutdown();
}
