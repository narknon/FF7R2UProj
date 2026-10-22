#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RebirthFxLinkLibrary.generated.h"

/**
 * Helpers for the Rebirth FX and material tools (Content/Python/rebirth_fx): the game's own, unmodified packages read
 * straight from its IoStore containers (the engine decompresses them), and a searchable list picker.
 *
 * Python: unreal.RebirthFxLinkLibrary.save_game_package_to_file("/Game/Effect/.../FX_X", "C:/.../FX_X.uasset")
 */
UCLASS()
class REBIRTHFXLIVELINK_API URebirthFxLinkLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Writes the game's own package (its zen bytes, as the game ships it) to Filename. Returns "" when done, else why not. */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|FX")
	static FString SaveGamePackageToFile(const FString& PackageName, const FString& Filename);

	/** Writes the container header of the game container that holds PackageName (its package store entries) to Filename;
	 * OutContainer gets the container's name (pakchunk4-WindowsNoEditor). Returns "" when done, else why not. */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|FX")
	static FString SaveGameContainerHeaderToFile(const FString& PackageName, const FString& Filename, FString& OutContainer);

	/** Game package names containing every space-separated word of Filter (case-insensitive), sorted, at most MaxResults. */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|FX")
	static TArray<FString> FindGamePackagesMatching(const FString& Filter, int32 MaxResults = 50000);

	/** The game's End\Content\Paks folder ("" when it was not found). */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|FX")
	static FString GetGamePaksDirectory();

	/** A modal window: Items with a search box. Returns the chosen item, or "" when cancelled. */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|FX")
	static FString PickFromList(const FString& Title, const FString& Prompt, const TArray<FString>& Items, const FString& InitialFilter);

	/**
	 * What the game needs to draw this material (or material instance) with a shader of its own, written to Directory:
	 *   material.hlsl  the shader code this editor generates for it (its material template, filled in: every node,
	 *                  material function, custom node and static switch already resolved)
	 *   material.json  its properties (domain, blend mode, shading models, two sided, ...), the values of its uniform
	 *                  expressions for this material or instance (the Material uniform buffer's constants), its textures
	 *                  (parameter, texture, sampler) and the parameter collections the code reads, in the code's order
	 * Returns "" when done, else why not. Waits for the material's shaders to finish compiling.
	 *
	 * Python: unreal.RebirthFxLinkLibrary.export_material_for_game(unreal.load_asset('/Game/X/M_X'), 'C:/out/M_X')
	 */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Materials")
	static FString ExportMaterialForGame(class UMaterialInterface* Material, const FString& Directory);
};
