#include "AssetTypeActions_EffectAppendixMesh.h"
#include "EffectAppendixMeshEditor.h"
#include "SEffectAppendixMeshEditorViewport.h"

void FAssetTypeActions_EffectAppendixMesh::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		UEffectAppendixMesh* EffectAppendixMesh = Cast<UEffectAppendixMesh>(*ObjIt);
		if (EffectAppendixMesh != nullptr)
		{
			TSharedRef<FEffectAppendixMeshEditor> NewEffectAppendixMeshEditor(new FEffectAppendixMeshEditor());
			NewEffectAppendixMeshEditor->InitEffectAppendixMeshEditor(Mode, EditWithinLevelEditor, EffectAppendixMesh);
		}
	}
}