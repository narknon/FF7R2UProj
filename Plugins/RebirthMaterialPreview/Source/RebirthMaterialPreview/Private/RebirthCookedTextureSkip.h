#pragma once

/**
 * Keeps a cook (Package Project, Alpakit) from waiting forever on textures that are already cooked.
 *
 * Game textures copied into the project (for example the textures in /Game/Character/Player/Common/Eye/Texture, which character
 * materials reference) are cooked packages. This engine cannot cook them again: UTexture::BeginCacheForCookedPlatformData
 * skips any package saved with PKG_FilterEditorOnly, but UTexture::IsCachedCookedPlatformDataLoaded then waits for
 * platform data that is never cached. The cooker keeps those packages in its save queue indefinitely; the log repeats
 * "Cooked packages N Packages Remain M" and the cook never finishes.
 *
 * Install() runs in commandlets only. When the cooker collects its packages it calls FGameDelegates' cook modification
 * delegate and, right after it, UAssetManager::ModifyCook, whose NeverCook output the cooker adds to its never-cook list
 * (the same list "Directories to never cook" fills). The delegate finds every cooked texture package in the asset
 * registry and puts URebirthCookAssetManagerProxy in place as the asset manager for that one call; the proxy restores the
 * real asset manager, runs its ModifyCook unchanged and appends those packages to the NeverCook output. Packages that use
 * the textures still cook and keep their references; the game loads its own copies at the same paths. Run with
 * -RebirthCookCookedTextures to turn it off.
 *
 * The same list also leaves out the cooked copies of the game's blueprints and data assets (RebirthCookedCopies.h; run
 * with -RebirthCookCookedCopies to cook those again), and the rebuilt, editable RM_Surface (/Game/Renderer/Material/RM_Surface,
 * Tools\RebuiltSurface) when it is in the project: the game has its own. Other cooked packages (materials, meshes,
 * skeletons, Bonamik/KDI data and so on) are not affected.
 */
namespace RebirthCookedTextureSkip
{
	void Install();
	void Uninstall();
}
