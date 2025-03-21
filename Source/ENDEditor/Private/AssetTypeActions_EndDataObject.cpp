#include "AssetTypeActions_EndDataObject.h"
#include "EndDataObjectEditor.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

void FAssetTypeActions_EndDataObject::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	/*EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		UObject* Object = *ObjIt; // Dereference the iterator to get the UObject*
		if (UEndDataObjectBase* Asset = Cast<UEndDataObjectBase>(Object)) {
			TSharedRef<FEndDataObjectEditor> DataObjectEditor = MakeShareable(new FEndDataObjectEditor());
			DataObjectEditor->InitEndDataObjectEditor(Mode, EditWithinLevelEditor, Asset);
		}
	}*/


	TArray<UEndDataObjectBase*> DataObjectsToOpen;
	TArray<UEndDataObjectBase*> InvalidDataObjects;

	for (UObject* Obj : InObjects)
	{
		UEndDataObjectBase* Table = Cast<UEndDataObjectBase>(Obj);
		if (Table)
		{
			if (Table->GetRowStruct())
			{
				DataObjectsToOpen.Add(Table);
			}
			else
			{
				DataObjectsToOpen.Add(Table);
			}
		}
	}

	if (InvalidDataObjects.Num() > 0)
	{
		FTextBuilder DataObjectsListText;
		DataObjectsListText.Indent();
		for (UEndDataObjectBase* DataObject : InvalidDataObjects)
		{
			const FName ResolvedRowStructName = DataObject->GetRowStructName();
			DataObjectsListText.AppendLineFormat(LOCTEXT("DataObject_MissingRowStructListEntry", "* {0} (Row Structure: {1})"), FText::FromString(DataObject->GetName()), FText::FromName(ResolvedRowStructName));
		}

		FText Title = LOCTEXT("DataTable_MissingRowStructTitle", "Continue?");
		const EAppReturnType::Type DlgResult = FMessageDialog::Open(
			EAppMsgType::YesNoCancel,
			FText::Format(LOCTEXT("DataObject_MissingRowStructMsg", "The following Data Objects are missing their row structure and will not be editable.\n\n{0}\n\nDo you want to open these data objects?"), DataObjectsListText.ToText()),
			&Title
		);

		switch (DlgResult)
		{
		case EAppReturnType::Yes:
			DataObjectsToOpen.Append(InvalidDataObjects);
			break;
		case EAppReturnType::Cancel:
			return;
		default:
			break;
		}
	}

	for (UEndDataObjectBase* DataObject : DataObjectsToOpen)
	{
		TSharedRef< FEndDataObjectEditor > NewDataObjectEditor(new FEndDataObjectEditor());
		NewDataObjectEditor->InitEndDataObjectEditor(EToolkitMode::Standalone, EditWithinLevelEditor, DataObject);
	}
}
#undef LOCTEXT_NAMESPACE
