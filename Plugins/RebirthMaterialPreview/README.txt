Rebirth Material and Effect Preview

Editor-only plugin for the End project (Plugins/RebirthMaterialPreview). Its skeleton
compatibility tools need the engine with Animation/RebirthSkeletonCompatibility.

All registered asset type actions are decorated using public AssetTools APIs.
Additional actions registered when editor modules load are decorated as well.
A generic UObject action protects game data types without an exact action.
Cooked Blueprints, generated classes, structs, enums, DataAssets, DataTables and
other types open a read-only scalar/reference/container-count inspector. It
does not instantiate a native asset editor or class Details customization,
compile a Blueprint, construct actors, execute gameplay, follow references,
or expand nested native data. This is protective opening, not proof of complete
cooked asset or gameplay compatibility. Editable assets retain original actions.

Cooked Material, MaterialInstanceConstant, Cascade ParticleSystem and Niagara
System double-click uses a runtime preview window. Editable assets continue
through the original asset action and graph editor. The window never saves,
duplicates, regenerates expressions, changes parent materials or recompiles
stripped graphs. Actual material/shader resources and runtime emitters are used.
Pause, Restart and Focus operate only on transient preview components.

Read-only resource diagnostics are available in Python/Blueprints:
  import json
  report = json.loads(unreal.RebirthMaterialDiagnosticsLibrary.get_material_diagnostics(material, True))
The optional True waits for existing editable-material compile jobs. It never
compiles a cooked graph. JSON includes current RHI feature/platform, per-quality
resource/map presence, finalized/success flags, compile errors, used textures,
base-material path and expression count. No shader-map presence is inferred.

Generic inspection and explicit loading diagnostics:
  unreal.RebirthMaterialDiagnosticsLibrary.get_asset_diagnostics(asset)
  unreal.RebirthMaterialDiagnosticsLibrary.load_asset_diagnostics('/Game/Path/Asset.Asset')
The load function writes before_native_load to a unique JSON under
Saved/RebirthMaterialPreview/Diagnostics before LoadObject, then overwrites it
with native_load_returned/native_load_failed and the inspection result. A fatal
native serializer/PostLoad failure can still terminate the process, leaving the
phase marker. Run suspect assets in a separate editor process for diagnostics.

The original asset actions are restored when the module shuts down. Original
type-specific context actions are delegated only for editable selections to
avoid graph-mutating commands on cooked assets. General Content Browser actions
are not replaced. The plugin depends on the installed Niagara plugin.

Limits:
- Cooked package load/serialization failures can occur before asset actions run.
- Cooked object/schema compatibility is not reconstructed by the inspector.
  It does not make cooked Blueprint gameplay executable or editable.
- Missing shader bytecode/libraries and textures remain missing; this plugin
  does not approximate a material with a replacement shader.
- Niagara systems require valid compiled runtime data and no pending compiler
  request. No Niagara graph editor or system view model is constructed.
- A standalone cooked Niagara emitter requires its compiled owning system and
  receives an explanatory window instead of unsafe system reconstruction.
- Gameplay actors, character bones, game-only data interfaces, parameters and
  scene dependencies are not manufactured. Asset validity checks cannot prove
  every native game-specific data interface will be safe.
- No engine DLL is patched and no runtime binary hook/injection is used.

Build with the engine's installed UnrealBuildTool as an Editor plugin against
the EndEditor target. Requires a compatible MSVC and Windows SDK.
