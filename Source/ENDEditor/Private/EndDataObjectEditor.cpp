#include "EndDataObjectEditor.h"
#include "EndDataObjectBase.h"
#include "ENDEditorModule.h"
#include "Dom/JsonObject.h"
#include "Editor.h"
#include "EditorStyleSet.h"
#include "Fonts/FontMeasure.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Commands/GenericCommands.h"
#include "Framework/Layout/Overscroll.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/Notifications/NotificationManager.h"
#include "HAL/PlatformApplicationMisc.h"
#include "IDocumentation.h"
#include "Misc/FeedbackContext.h"
#include "Misc/FileHelper.h"
#include "Modules/ModuleManager.h"
#include "Policies/PrettyJsonPrintPolicy.h"
#include "ScopedTransaction.h"
#include "SDataObjectListViewRow.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SScrollBar.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/SToolTip.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SHyperlink.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/Layout/SSeparator.h"
#include "SourceCodeNavigation.h"
#include "PropertyEditorModule.h"
#include "UObject/StructOnScope.h"
#include "Toolkits/GlobalEditorCommonCommands.h"
#include "Toolkits/AssetEditorManager.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "IStructureDetailsView.h"

#define LOCTEXT_NAMESPACE "EndDataObjectEditor"

const FName FEndDataObjectEditor::DataObjectTabId("DataObjectEditor_DataObject");
const FName FEndDataObjectEditor::DataObjectDetailsTabId("DataObjectEditor_DataObjectDetails");
const FName FEndDataObjectEditor::RowEditorTabId("DataObjectEditor_RowEditor");
const FName FEndDataObjectEditor::RowNameColumnId("RowName");
const FName FEndDataObjectEditor::RowNumberColumnId("RowNumber");
const FName FEndDataObjectEditor::RowDragDropColumnId("RowDragDrop");

FEndDataObjectEditor::FEndDataObjectEditor()
    : RowNameColumnWidth(0)
    , RowNumberColumnWidth(0)
    , HighlightedVisibleRowIndex(INDEX_NONE)
    , SortMode(EColumnSortMode::Ascending)
{
}

FEndDataObjectEditor::~FEndDataObjectEditor()
{
    GEditor->UnregisterForUndo(this);

    UEndDataObjectBase* DataObject = GetEditableDataObject();
    if (DataObject)
    {
        SaveLayoutData();
    }
}

void FEndDataObjectEditor::PostUndo(bool bSuccess)
{
    HandleUndoRedo();
}

void FEndDataObjectEditor::PostRedo(bool bSuccess)
{
    HandleUndoRedo();
}

void FEndDataObjectEditor::HandleUndoRedo()
{
    const UEndDataObjectBase* DataObject = GetDataObject();
    if (DataObject)
    {
        HandlePostChange();
        CallbackOnDataObjectUndoRedo.ExecuteIfBound();
    }
}

void FEndDataObjectEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_Data Object Editor", "Data Object Editor"));

    FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

    CreateAndRegisterDataObjectTab(InTabManager);
    CreateAndRegisterDataObjectDetailsTab(InTabManager);
    CreateAndRegisterRowEditorTab(InTabManager);

    /*FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
    InTabManager->RegisterTabSpawner("PropertiesTab", FOnSpawnTab::CreateRaw(this, &FEndDataObjectEditor::SpawnRowMapTab))
        .SetDisplayName(NSLOCTEXT("EndDataObjectEditor", "PropertiesTab", "Properties"));*/
}

void FEndDataObjectEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

    //InTabManager->UnregisterTabSpawner("PropertiesTab");

    InTabManager->UnregisterTabSpawner(DataObjectTabId);
    InTabManager->UnregisterTabSpawner(DataObjectDetailsTabId);
    InTabManager->UnregisterTabSpawner(RowEditorTabId);

    DataObjectTabWidget.Reset();
    RowEditorTabWidget.Reset();
}

void FEndDataObjectEditor::CreateAndRegisterDataObjectTab(const TSharedRef<class FTabManager>& InTabManager)
{
    DataObjectTabWidget = CreateContentBox();

    InTabManager->RegisterTabSpawner(DataObjectTabId, FOnSpawnTab::CreateSP(this, &FEndDataObjectEditor::SpawnTab_DataObject))
        .SetDisplayName(LOCTEXT("DataObjectTab", "Data Object"))
        .SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FEndDataObjectEditor::CreateAndRegisterDataObjectDetailsTab(const TSharedRef<class FTabManager>& InTabManager)
{
    FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
    FDetailsViewArgs DetailsViewArgs(/*bUpdateFromSelection=*/ false, /*bLockable=*/ false, /*bAllowSearch=*/ true, /*InNameAreaSettings=*/ FDetailsViewArgs::HideNameArea, /*bHideSelectionTip=*/ true);
    PropertyView = EditModule.CreateDetailView(DetailsViewArgs);

    InTabManager->RegisterTabSpawner(DataObjectDetailsTabId, FOnSpawnTab::CreateSP(this, &FEndDataObjectEditor::SpawnTab_DataObjectDetails))
        .SetDisplayName(LOCTEXT("DataObjectDetailsTab", "Data Object Details"))
        .SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FEndDataObjectEditor::CreateAndRegisterRowEditorTab(const TSharedRef<class FTabManager>& InTabManager)
{
    RowEditorTabWidget = CreateRowEditorBox();

    InTabManager->RegisterTabSpawner(RowEditorTabId, FOnSpawnTab::CreateSP(this, &FEndDataObjectEditor::SpawnTab_RowEditor))
        .SetDisplayName(LOCTEXT("RowEditorTab", "Row Editor"))
        .SetGroup(WorkspaceMenuCategory.ToSharedRef());
}
bool FEndDataObjectEditor::CanEditRows() const
{
	return true;
}

UEndDataObjectBase* FEndDataObjectEditor::GetEditableDataObject() const
{
    return Cast<UEndDataObjectBase>(GetEditingObject());
}

FName FEndDataObjectEditor::GetToolkitFName() const
{
    return FName("EndDataObjectEditor");
}

FText FEndDataObjectEditor::GetBaseToolkitName() const
{
    return LOCTEXT("AppLabel", "End Data Object Editor");
}

FString FEndDataObjectEditor::GetWorldCentricTabPrefix() const
{
    return LOCTEXT("WorldCentricTabPrefix", "Data Object ").ToString();
}

FLinearColor FEndDataObjectEditor::GetWorldCentricTabColorScale() const
{
    return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

FString FEndDataObjectEditor::GetDocumentationLink() const
{
	return FString(TEXT("Gameplay/DataDriven"));
}

void FEndDataObjectEditor::OnAddClicked()
{
	UEndDataObjectBase* DataObject = GetEditableDataObject();

	if (DataObject)
	{		
		FName NewName = DataTableUtils::MakeValidName(TEXT("NewRow"));
		while (DataObject->GetRowMap().Contains(NewName))
		{
			NewName.SetNumber(NewName.GetNumber() + 1);
		}

		FDataObjectEditorUtils::AddRow(DataObject, NewName);
		FDataObjectEditorUtils::SelectRow(DataObject, NewName);

		SetDefaultSort();
	}
}

void FEndDataObjectEditor::OnRemoveClicked()
{
	DeleteSelectedRow();
}

FReply FEndDataObjectEditor::OnMoveRowClicked(FDataObjectEditorUtils::ERowMoveDirection MoveDirection)
{
	UEndDataObjectBase* DataObject = GetEditableDataObject();

	if (DataObject)
	{
		FDataObjectEditorUtils::MoveRow(DataObject, HighlightedRowName, MoveDirection);
	}
	return FReply::Handled();
}

FReply FEndDataObjectEditor::OnMoveToExtentClicked(FDataObjectEditorUtils::ERowMoveDirection MoveDirection)
{
	UEndDataObjectBase* DataObject = GetEditableDataObject();

	if (DataObject)
	{
		// We move by the row map size, as FDataObjectEditorUtils::MoveRow will automatically clamp this as appropriate
		FDataObjectEditorUtils::MoveRow(DataObject, HighlightedRowName, MoveDirection, DataObject->GetRowMap().Num());
		FDataObjectEditorUtils::SelectRow(DataObject, HighlightedRowName);

		SetDefaultSort();
	}
	return FReply::Handled();
}

void FEndDataObjectEditor::OnCopyClicked()
{
	UEndDataObjectBase* DataObject = GetEditableDataObject();
	if (DataObject)
	{
		CopySelectedRow();
	}
}

void FEndDataObjectEditor::OnPasteClicked()
{
	UEndDataObjectBase* DataObject = GetEditableDataObject();
	if (DataObject)
	{
		PasteOnSelectedRow();
	}
}

void FEndDataObjectEditor::OnDuplicateClicked()
{
	UEndDataObjectBase* DataObject = GetEditableDataObject();
	if (DataObject)
	{
		DuplicateSelectedRow();
	}
}

void FEndDataObjectEditor::SetDefaultSort()
{
	SortMode = EColumnSortMode::Ascending;
	SortByColumn = FEndDataObjectEditor::RowNumberColumnId;
}

EColumnSortMode::Type FEndDataObjectEditor::GetColumnSortMode(const FName ColumnId) const
{
	if (SortByColumn != ColumnId)
	{
		return EColumnSortMode::None;
	}

	return SortMode;
}

void FEndDataObjectEditor::InitEndDataObjectEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UEndDataObjectBase* InEndDataObject)
{
	EndDataObject = InEndDataObject;

	TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_DataObjectEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(true)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(DataObjectTabId, ETabState::OpenedTab)
				->AddTab(DataObjectDetailsTabId, ETabState::OpenedTab)
				->SetForegroundTab(DataObjectTabId)
			)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(RowEditorTabId, ETabState::OpenedTab)
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, FENDEditorModule::DataObjectEditorAppIdentifier, StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, InEndDataObject);

	FENDEditorModule& DataObjectEditorModule = FModuleManager::LoadModuleChecked<FENDEditorModule>("ENDEditor");
	AddMenuExtender(DataObjectEditorModule.GetMenuExtensibilityManager()->GetAllExtenders(GetToolkitCommands(), GetEditingObjects()));

	TSharedPtr<FExtender> ToolbarExtender = DataObjectEditorModule.GetToolBarExtensibilityManager()->GetAllExtenders(GetToolkitCommands(), GetEditingObjects());
	ExtendToolbar(ToolbarExtender);

	AddToolbarExtender(ToolbarExtender);

	RegenerateMenusAndToolbars();

	// Support undo/redo
	GEditor->RegisterForUndo(this);

	// @todo toolkit world centric editing
	/*// Setup our tool's layout
	if( IsWorldCentricAssetEditor() )
	{
		const FString TabInitializationPayload(TEXT(""));		// NOTE: Payload not currently used for table properties
		SpawnToolkitTab( DataObjectTabId, TabInitializationPayload, EToolkitTabSpot::Details );
	}*/

	// asset editor commands here
	ToolkitCommands->MapAction(FGenericCommands::Get().Copy, FExecuteAction::CreateSP(this, &FEndDataObjectEditor::CopySelectedRow));
	ToolkitCommands->MapAction(FGenericCommands::Get().Paste, FExecuteAction::CreateSP(this, &FEndDataObjectEditor::PasteOnSelectedRow));
	ToolkitCommands->MapAction(FGenericCommands::Get().Duplicate, FExecuteAction::CreateSP(this, &FEndDataObjectEditor::DuplicateSelectedRow));
	ToolkitCommands->MapAction(FGenericCommands::Get().Rename, FExecuteAction::CreateSP(this, &FEndDataObjectEditor::RenameSelectedRowCommand));
	ToolkitCommands->MapAction(FGenericCommands::Get().Delete, FExecuteAction::CreateSP(this, &FEndDataObjectEditor::DeleteSelectedRow));
}

void FEndDataObjectEditor::ExtendToolbar(TSharedPtr<FExtender> Extender)
{
	Extender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateSP(this, &FEndDataObjectEditor::FillToolbar)
	);

}


void FEndDataObjectEditor::FillToolbar(FToolBarBuilder& ToolbarBuilder)
{
	ToolbarBuilder.BeginSection("DataObjectCommands");
	{
		ToolbarBuilder.AddToolBarButton(
			FUIAction(
				FExecuteAction::CreateSP(this, &FEndDataObjectEditor::Reimport_Execute),
				FCanExecuteAction::CreateSP(this, &FEndDataObjectEditor::CanReimport)),
			NAME_None,
			LOCTEXT("ReimportText", "Reimport"),
			LOCTEXT("ReimportTooltip", "Reimport this DataObject"),
			FSlateIcon(FEditorStyle::GetStyleSetName(), "AssetEditor.ReimportAsset"));

		ToolbarBuilder.AddSeparator();

		ToolbarBuilder.AddToolBarButton(
			FUIAction(FExecuteAction::CreateSP(this, &FEndDataObjectEditor::OnAddClicked)),
			NAME_None,
			LOCTEXT("AddIconText", "Add"),
			LOCTEXT("AddRowToolTip", "Add a new row to the Data Object"),
			FSlateIcon(FEditorStyle::GetStyleSetName(), "DataObjectEditor.Add"));
		ToolbarBuilder.AddToolBarButton(
			FUIAction(FExecuteAction::CreateSP(this, &FEndDataObjectEditor::OnCopyClicked)),
			NAME_None,
			LOCTEXT("CopyIconText", "Copy"),
			LOCTEXT("CopyToolTip", "Copy the currently selected row"),
			FSlateIcon(FEditorStyle::GetStyleSetName(), "DataObjectEditor.Copy"));
		ToolbarBuilder.AddToolBarButton(
			FUIAction(FExecuteAction::CreateSP(this, &FEndDataObjectEditor::OnPasteClicked)),
			NAME_None,
			LOCTEXT("PasteIconText", "Paste"),
			LOCTEXT("PasteToolTip", "Paste on the currently selected row"),
			FSlateIcon(FEditorStyle::GetStyleSetName(), "DataObjecttEditor.Paste"));
		ToolbarBuilder.AddToolBarButton(
			FUIAction(FExecuteAction::CreateSP(this, &FEndDataObjectEditor::OnDuplicateClicked)),
			NAME_None,
			LOCTEXT("DuplicateIconText", "Duplicate"),
			LOCTEXT("DuplicateToolTip", "Duplicate the currently selected row"),
			FSlateIcon(FEditorStyle::GetStyleSetName(), "DataObjectEditor.Duplicate"));
		ToolbarBuilder.AddToolBarButton(
			FUIAction(FExecuteAction::CreateSP(this, &FEndDataObjectEditor::OnRemoveClicked)),
			NAME_None,
			LOCTEXT("RemoveRowIconText", "Remove"),
			LOCTEXT("RemoveRowToolTip", "Remove the currently selected row from the Data Object"),
			FSlateIcon(FEditorStyle::GetStyleSetName(), "DataObjectEditor.Remove"));
	}
	ToolbarBuilder.EndSection();

}


FSlateColor FEndDataObjectEditor::GetRowTextColor(FName RowName) const
{
	if (RowName == HighlightedRowName)
	{
		return FSlateColor(FColorList::Orange);
	}
	//return FSlateColor::UseForeground();
	return FSlateColor(FColorList::DarkSlateGrey);
}

FText FEndDataObjectEditor::GetCellText(FDataObjectEditorRowListViewDataPtr InRowDataPointer, int32 ColumnIndex) const
{
	if (InRowDataPointer.IsValid() && ColumnIndex < InRowDataPointer->CellData.Num())
	{
		return InRowDataPointer->CellData[ColumnIndex];
	}

	return FText();
}

FText FEndDataObjectEditor::GetCellToolTipText(FDataObjectEditorRowListViewDataPtr InRowDataPointer, int32 ColumnIndex) const
{
	FText TooltipText;

	if (ColumnIndex < AvailableColumns.Num())
	{
		TooltipText = AvailableColumns[ColumnIndex]->DisplayName;
	}

	if (InRowDataPointer.IsValid() && ColumnIndex < InRowDataPointer->CellData.Num())
	{
		TooltipText = FText::Format(LOCTEXT("ColumnRowNameFmt", "{0}: {1}"), TooltipText, InRowDataPointer->CellData[ColumnIndex]);
	}

	return TooltipText;
}

float FEndDataObjectEditor::GetRowNumberColumnWidth() const
{
	return RowNumberColumnWidth;
}

void FEndDataObjectEditor::RefreshRowNumberColumnWidth()
{

	TSharedRef<FSlateFontMeasure> FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	const FTextBlockStyle& CellTextStyle = FEditorStyle::GetWidgetStyle<FTextBlockStyle>("DataObjectEditor.CellText");
	const float CellPadding = 10.0f;

	for (const FDataObjectEditorRowListViewDataPtr& RowData : AvailableRows)
	{
		const float RowNumberWidth = FontMeasure->Measure(FString::FromInt(RowData->RowNum), CellTextStyle.Font).X + CellPadding;
		RowNumberColumnWidth = FMath::Max(RowNumberColumnWidth, RowNumberWidth);
	}

}

void FEndDataObjectEditor::OnRowNumberColumnResized(const float NewWidth)
{
	RowNumberColumnWidth = NewWidth;
}

float FEndDataObjectEditor::GetRowNameColumnWidth() const
{
	return RowNameColumnWidth;
}

void FEndDataObjectEditor::RefreshRowNameColumnWidth()
{

	TSharedRef<FSlateFontMeasure> FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	const FTextBlockStyle& CellTextStyle = FEditorStyle::GetWidgetStyle<FTextBlockStyle>("DataObjectEditor.CellText");
	static const float CellPadding = 10.0f;

	for (const FDataObjectEditorRowListViewDataPtr& RowData : AvailableRows)
	{
		const float RowNameWidth = FontMeasure->Measure(RowData->DisplayName, CellTextStyle.Font).X + CellPadding;
		RowNameColumnWidth = FMath::Max(RowNameColumnWidth, RowNameWidth);
	}

}

float FEndDataObjectEditor::GetColumnWidth(const int32 ColumnIndex) const
{
	if (ColumnWidths.IsValidIndex(ColumnIndex))
	{
		return ColumnWidths[ColumnIndex].CurrentWidth;
	}
	return 0.0f;
}

void FEndDataObjectEditor::OnColumnResized(const float NewWidth, const int32 ColumnIndex)
{
	if (ColumnWidths.IsValidIndex(ColumnIndex))
	{
		FColumnWidth& ColumnWidth = ColumnWidths[ColumnIndex];
		ColumnWidth.bIsAutoSized = false;
		ColumnWidth.CurrentWidth = NewWidth;

		// Update the persistent column widths in the layout data
		{
			if (!LayoutData.IsValid())
			{
				LayoutData = MakeShareable(new FJsonObject());
			}

			TSharedPtr<FJsonObject> LayoutColumnWidths;
			if (!LayoutData->HasField(TEXT("ColumnWidths")))
			{
				LayoutColumnWidths = MakeShareable(new FJsonObject());
				LayoutData->SetObjectField(TEXT("ColumnWidths"), LayoutColumnWidths);
			}
			else
			{
				LayoutColumnWidths = LayoutData->GetObjectField(TEXT("ColumnWidths"));
			}

			const FString& ColumnName = AvailableColumns[ColumnIndex]->ColumnId.ToString();
			LayoutColumnWidths->SetNumberField(ColumnName, NewWidth);
		}
	}
}

void FEndDataObjectEditor::OnRowNameColumnResized(const float NewWidth)
{
	RowNameColumnWidth = NewWidth;
}

void FEndDataObjectEditor::LoadLayoutData()
{
	LayoutData.Reset();

	const UEndDataObjectBase* DataObject = GetDataObject();
	if (!DataObject)
	{
		return;
	}

	const FString LayoutDataFilename = FPaths::ProjectSavedDir() / TEXT("AssetData") / TEXT("DataObjectEditorLayout") / DataObject->GetName() + TEXT(".json");

	FString JsonText;
	if (FFileHelper::LoadFileToString(JsonText, *LayoutDataFilename))
	{
		TSharedRef< TJsonReader<TCHAR> > JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonText);
		FJsonSerializer::Deserialize(JsonReader, LayoutData);
	}
}

void FEndDataObjectEditor::SaveLayoutData()
{
	const UEndDataObjectBase* DataObject = GetDataObject();
	if (!DataObject || !LayoutData.IsValid())
	{
		return;
	}

	const FString LayoutDataFilename = FPaths::ProjectSavedDir() / TEXT("AssetData") / TEXT("DataObjectEditorLayout") / DataObject->GetName() + TEXT(".json");

	FString JsonText;
	TSharedRef< TJsonWriter< TCHAR, TPrettyJsonPrintPolicy<TCHAR> > > JsonWriter = TJsonWriterFactory< TCHAR, TPrettyJsonPrintPolicy<TCHAR> >::Create(&JsonText);
	if (FJsonSerializer::Serialize(LayoutData.ToSharedRef(), JsonWriter))
	{
		FFileHelper::SaveStringToFile(JsonText, *LayoutDataFilename);
	}
}

TSharedRef<ITableRow> FEndDataObjectEditor::MakeRowWidget(FDataObjectEditorRowListViewDataPtr InRowDataPtr, const TSharedRef<STableViewBase>& OwnerTable)
{
	return
		SNew(SDataObjectListViewRow, OwnerTable)
		.DataObjectEditor(SharedThis(this))
		.RowDataPtr(InRowDataPtr)
		.IsEditable(CanEditRows());
}

TSharedRef<SWidget> FEndDataObjectEditor::MakeCellWidget(FDataObjectEditorRowListViewDataPtr InRowDataPtr, const int32 InRowIndex, const FName& InColumnId)
{
	int32 ColumnIndex = 0;
	for (; ColumnIndex < AvailableColumns.Num(); ++ColumnIndex)
	{
		const FDataObjectEditorColumnHeaderDataPtr& ColumnData = AvailableColumns[ColumnIndex];
		if (ColumnData->ColumnId == InColumnId)
		{
			break;
		}
	}

	// Valid column ID?
	if (AvailableColumns.IsValidIndex(ColumnIndex) && InRowDataPtr->CellData.IsValidIndex(ColumnIndex))
	{
		return SNew(SBox)
			.Padding(FMargin(4, 2, 4, 2))
			[
				SNew(STextBlock)
				.TextStyle(FEditorStyle::Get(), "DataObjectEditor.CellText")
			.ColorAndOpacity(this, &FEndDataObjectEditor::GetRowTextColor, InRowDataPtr->RowId)
			.Text(this, &FEndDataObjectEditor::GetCellText, InRowDataPtr, ColumnIndex)
			.HighlightText(this, &FEndDataObjectEditor::GetFilterText)
			.ToolTipText(this, &FEndDataObjectEditor::GetCellToolTipText, InRowDataPtr, ColumnIndex)
			];
	}

	return SNullWidget::NullWidget;
}

void FEndDataObjectEditor::OnRowSelectionChanged(FDataObjectEditorRowListViewDataPtr InNewSelection, ESelectInfo::Type InSelectInfo)
{
	const bool bSelectionChanged = !InNewSelection.IsValid() || InNewSelection->RowId != HighlightedRowName;
	const FName NewRowName = (InNewSelection.IsValid()) ? InNewSelection->RowId : NAME_None;

	SetHighlightedRow(NewRowName);

	if (bSelectionChanged)
	{
		CallbackOnRowHighlighted.ExecuteIfBound(HighlightedRowName);
	}
}

TSharedRef<SDockTab> FEndDataObjectEditor::SpawnPropertiesTab(const FSpawnTabArgs& Args) {
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

    FDetailsViewArgs DetailsViewArgs;
    DetailsViewArgs.bAllowSearch = true;
    DetailsViewArgs.bLockable = false;
    DetailsViewArgs.bUpdatesFromSelection = false;

    TSharedRef<IDetailsView> DetailsView = PropertyModule.CreateDetailView(DetailsViewArgs);
    DetailsView->SetObject(EndDataObject);

    return SNew(SDockTab)
        .Label(NSLOCTEXT("EndDataObjectEditor", "PropertiesTab", "Properties"))
        [DetailsView];
}

TSharedRef<SDockTab> FEndDataObjectEditor::SpawnRowMapTab(const FSpawnTabArgs& Args) {
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

    TSharedRef<SScrollBox> ScrollBox = SNew(SScrollBox);

    // Create a details view for each struct in RowMap
    for (const auto& Pair : EndDataObject->RowMap) {
        FString Key = Pair.Key.ToString();
        uint8* RowData = Pair.Value;

        if (RowData) {
            // Create a FStructOnScope for the struct
            TSharedRef<FStructOnScope> StructOnScope = MakeShareable(new FStructOnScope(EndDataObject->RowStruct));
            FMemory::Memcpy(StructOnScope->GetStructMemory(), RowData, EndDataObject->RowStruct->GetStructureSize());

            // Create a struct details view
            TSharedRef<IStructureDetailsView> StructDetailsView = PropertyModule.CreateStructureDetailView(
                FDetailsViewArgs(), // Details view arguments
                FStructureDetailsViewArgs(), // Struct details view arguments
                StructOnScope // The struct data
            );
            StructDetailsView->SetCustomName(FText::FromString(Key));

            ScrollBox->AddSlot()
            [
                SNew(SVerticalBox)
                 + SVerticalBox::Slot()
                .AutoHeight()
                [
                    SNew(STextBlock)
                    .Text(FText::FromString(FString::Printf(TEXT("Key: %s"), *Key)))
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    StructDetailsView->GetWidget().ToSharedRef()
                ]
            ];
        }
    }

    return SNew(SDockTab)
        .Label(NSLOCTEXT("CustomAssetEditor", "RowMapTab", "RowMap"))
        [ScrollBox];
}

const UEndDataObjectBase* FEndDataObjectEditor::GetDataObject() const
{
    return Cast<const UEndDataObjectBase>(GetEditingObject());
}

void FEndDataObjectEditor::HandlePostChange()
{
    // We need to cache and restore the selection here as RefreshCachedDataObject will re-create the list view items
    const FName CachedSelection = HighlightedRowName;
    HighlightedRowName = NAME_None;
    RefreshCachedDataObject(CachedSelection, true/*bUpdateEvenIfValid*/);
}

void FEndDataObjectEditor::RefreshCachedDataObject(const FName InCachedSelection, const bool bUpdateEvenIfValid)
{
	UEndDataObjectBase* DataObject = GetEditableDataObject();
	TArray<FDataObjectEditorColumnHeaderDataPtr> PreviousColumns = AvailableColumns;

	FDataObjectEditorUtils::CacheDataObjectForEditing(DataObject, AvailableColumns, AvailableRows);

	// Update the desired width of the row names and numbers column
	// This prevents it growing or shrinking as you scroll the list view
	RefreshRowNumberColumnWidth();
	RefreshRowNameColumnWidth();

	// Setup the default auto-sized columns
	ColumnWidths.SetNum(AvailableColumns.Num());
	for (int32 ColumnIndex = 0; ColumnIndex < AvailableColumns.Num(); ++ColumnIndex)
	{
		const FDataObjectEditorColumnHeaderDataPtr& ColumnData = AvailableColumns[ColumnIndex];
		FColumnWidth& ColumnWidth = ColumnWidths[ColumnIndex];
		ColumnWidth.CurrentWidth = FMath::Clamp(ColumnData->DesiredColumnWidth, 10.0f, 400.0f); // Clamp auto-sized columns to a reasonable limit
	}

	// Load the persistent column widths from the layout data
	{
		const TSharedPtr<FJsonObject>* LayoutColumnWidths = nullptr;
		if (LayoutData.IsValid() && LayoutData->TryGetObjectField(TEXT("ColumnWidths"), LayoutColumnWidths))
		{
			for (int32 ColumnIndex = 0; ColumnIndex < AvailableColumns.Num(); ++ColumnIndex)
			{
				const FDataObjectEditorColumnHeaderDataPtr& ColumnData = AvailableColumns[ColumnIndex];

				double LayoutColumnWidth = 0.0f;
				if ((*LayoutColumnWidths)->TryGetNumberField(ColumnData->ColumnId.ToString(), LayoutColumnWidth))
				{
					FColumnWidth& ColumnWidth = ColumnWidths[ColumnIndex];
					ColumnWidth.bIsAutoSized = false;
					ColumnWidth.CurrentWidth = static_cast<float>(LayoutColumnWidth);
				}
			}
		}
	}

	if (PreviousColumns != AvailableColumns)
	{
		ColumnNamesHeaderRow->ClearColumns();

		if (CanEditRows())
		{
			ColumnNamesHeaderRow->AddColumn(
				SHeaderRow::Column(RowDragDropColumnId)
				[
					SNew(SBox)
					.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.ToolTip(IDocumentation::Get()->CreateToolTip(
					LOCTEXT("DataObjectRowHandleTooltip", "Drag Drop Handles"),
					nullptr,
					*FDataObjectEditorUtils::VariableTypesTooltipDocLink,
					TEXT("DataObjectRowHandle")))
				[
					SNew(STextBlock)
					.Text(FText::GetEmpty())
				]
				]
			);
		}

		ColumnNamesHeaderRow->AddColumn(
			SHeaderRow::Column(RowNumberColumnId)
			//.SortMode(this, &FEndDataObjectEditor::GetColumnSortMode, RowNumberColumnId)
			//.OnSort(this, &FEndDataObjectEditor::OnColumnNumberSortModeChanged)
			.ManualWidth(this, &FEndDataObjectEditor::GetRowNumberColumnWidth)
			.OnWidthChanged(this, &FEndDataObjectEditor::OnRowNumberColumnResized)
			[
				SNew(SBox)
				.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			.ToolTip(IDocumentation::Get()->CreateToolTip(
				LOCTEXT("DataObjectRowIndexTooltip", "Row Index"),
				nullptr,
				*FDataObjectEditorUtils::VariableTypesTooltipDocLink,
				TEXT("DataObjectRowIndex")))
			[
				SNew(STextBlock)
				.Text(FText::GetEmpty())
			]
			]

		);

		ColumnNamesHeaderRow->AddColumn(
			SHeaderRow::Column(RowNameColumnId)
			.DefaultLabel(LOCTEXT("DataObjectRowName", "Row Name"))
			.ManualWidth(this, &FEndDataObjectEditor::GetRowNameColumnWidth)
			.OnWidthChanged(this, &FEndDataObjectEditor::OnRowNameColumnResized)
			//.SortMode(this, &FEndDataObjectEditor::GetColumnSortMode, RowNameColumnId)
			//.OnSort(this, &FEndDataObjectEditor::OnColumnNameSortModeChanged)
		);

		for (int32 ColumnIndex = 0; ColumnIndex < AvailableColumns.Num(); ++ColumnIndex)
		{
			const FDataObjectEditorColumnHeaderDataPtr& ColumnData = AvailableColumns[ColumnIndex];

			ColumnNamesHeaderRow->AddColumn(
				SHeaderRow::Column(ColumnData->ColumnId)
				.DefaultLabel(ColumnData->DisplayName)
				.ManualWidth(TAttribute<float>::Create(TAttribute<float>::FGetter::CreateSP(this, &FEndDataObjectEditor::GetColumnWidth, ColumnIndex)))
				.OnWidthChanged(this, &FEndDataObjectEditor::OnColumnResized, ColumnIndex)
				//.SortMode(this, &FEndDataObjectEditor::GetColumnSortMode, ColumnData->ColumnId)
				//.OnSort(this, &FEndDataObjectEditor::OnColumnSortModeChanged)
				[
					SNew(SBox)
					.Padding(FMargin(0, 4, 0, 4))
				.VAlign(VAlign_Fill)
				.ToolTip(IDocumentation::Get()->CreateToolTip(FDataObjectEditorUtils::GetRowTypeInfoTooltipText(ColumnData), nullptr, *FDataObjectEditorUtils::VariableTypesTooltipDocLink, FDataObjectEditorUtils::GetRowTypeTooltipDocExcerptName(ColumnData)))
				[
					SNew(STextBlock)
					.Justification(ETextJustify::Center)
				.Text(ColumnData->DisplayName)
				]
				]
			);
		}
	}

	UpdateVisibleRows(InCachedSelection, bUpdateEvenIfValid);

	if (PropertyView.IsValid())
	{
		PropertyView->SetObject(DataObject);
	}
}

void FEndDataObjectEditor::UpdateVisibleRows(const FName InCachedSelection, const bool bUpdateEvenIfValid)
{
	if (ActiveFilterText.IsEmptyOrWhitespace())
	{
		VisibleRows = AvailableRows;
	}
	else
	{
		VisibleRows.Empty(AvailableRows.Num());

		const FString& ActiveFilterString = ActiveFilterText.ToString();
		for (const FDataObjectEditorRowListViewDataPtr& RowData : AvailableRows)
		{
			bool bPassesFilter = false;

			if (RowData->DisplayName.ToString().Contains(ActiveFilterString))
			{
				bPassesFilter = true;
			}
			else
			{
				for (const FText& CellText : RowData->CellData)
				{
					if (CellText.ToString().Contains(ActiveFilterString))
					{
						bPassesFilter = true;
						break;
					}
				}
			}

			if (bPassesFilter)
			{
				VisibleRows.Add(RowData);
			}
		}
	}

	CellsListView->RequestListRefresh();
	RestoreCachedSelection(InCachedSelection, bUpdateEvenIfValid);
}

void FEndDataObjectEditor::RestoreCachedSelection(const FName InCachedSelection, const bool bUpdateEvenIfValid)
{
	// Validate the requested selection to see if it matches a known row
	bool bSelectedRowIsValid = false;
	if (!InCachedSelection.IsNone())
	{
		bSelectedRowIsValid = VisibleRows.ContainsByPredicate([&InCachedSelection](const FDataObjectEditorRowListViewDataPtr& RowData) -> bool
			{
				return RowData->RowId == InCachedSelection;
			});
	}

	// Apply the new selection (if required)
	if (!bSelectedRowIsValid)
	{
		SetHighlightedRow((VisibleRows.Num() > 0) ? VisibleRows[0]->RowId : NAME_None);
		CallbackOnRowHighlighted.ExecuteIfBound(HighlightedRowName);
	}
	else if (bUpdateEvenIfValid)
	{
		SetHighlightedRow(InCachedSelection);
		CallbackOnRowHighlighted.ExecuteIfBound(HighlightedRowName);
	}
}

void FEndDataObjectEditor::CopySelectedRow()
{
	UEndDataObjectBase* DataObjectPtr = Cast<UEndDataObjectBase>(GetEditingObject());
	uint8* RowPtr = DataObjectPtr ? DataObjectPtr->GetRowMap().FindRef(HighlightedRowName) : nullptr;

	if (!RowPtr || !DataObjectPtr->RowStruct)
		return;

	FString ClipboardValue;
	DataObjectPtr->RowStruct->ExportText(ClipboardValue, RowPtr, RowPtr, DataObjectPtr, PPF_Copy, nullptr);

	FPlatformApplicationMisc::ClipboardCopy(*ClipboardValue);
}

void FEndDataObjectEditor::PasteOnSelectedRow()
{
	UEndDataObjectBase* DataObjectPtr = Cast<UEndDataObjectBase>(GetEditingObject());
	uint8* RowPtr = DataObjectPtr ? DataObjectPtr->GetRowMap().FindRef(HighlightedRowName) : nullptr;

	if (!RowPtr || !DataObjectPtr->RowStruct)
		return;

	const FScopedTransaction Transaction(LOCTEXT("PasteDataObjectRow", "Paste Data Object Row"));
	DataObjectPtr->Modify();

	FString ClipboardValue;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardValue);

	FDataObjectEditorUtils::BroadcastPreChange(DataObjectPtr, FDataObjectEditorUtils::EDataObjectChangeInfo::RowData);

	const TCHAR* Result = nullptr;// DataObjectPtr->RowStruct->ImportText(*ClipboardValue, RowPtr, DataObjectPtr, PPF_Copy, GWarn, GetPathNameSafe(DataObjectPtr->RowStruct));

	DataObjectPtr->HandleDataObjectChanged(HighlightedRowName);
	DataObjectPtr->MarkPackageDirty();

	FDataObjectEditorUtils::BroadcastPostChange(DataObjectPtr, FDataObjectEditorUtils::EDataObjectChangeInfo::RowData);

	if (Result == nullptr)
	{
		FNotificationInfo Info(LOCTEXT("FailedPaste", "Failed to paste row"));
		FSlateNotificationManager::Get().AddNotification(Info);
	}
}

void FEndDataObjectEditor::DuplicateSelectedRow()
{
	UEndDataObjectBase* DataObjectPtr = Cast<UEndDataObjectBase>(GetEditingObject());
	FName NewName = HighlightedRowName;

	if (NewName == NAME_None || DataObjectPtr == nullptr)
	{
		return;
	}

	const TArray<FName> ExistingNames = DataObjectPtr->GetRowNames();
	while (ExistingNames.Contains(NewName))
	{
		NewName.SetNumber(NewName.GetNumber() + 1);
	}

	FDataObjectEditorUtils::DuplicateRow(DataObjectPtr, HighlightedRowName, NewName);
	FDataObjectEditorUtils::SelectRow(DataObjectPtr, NewName);
}

void FEndDataObjectEditor::RenameSelectedRowCommand()
{
	UEndDataObjectBase* DataObjectPtr = Cast<UEndDataObjectBase>(GetEditingObject());
	FName NewName = HighlightedRowName;

	if (NewName == NAME_None || DataObjectPtr == nullptr)
	{
		return;
	}

	if (VisibleRows.IsValidIndex(HighlightedVisibleRowIndex))
	{
		TSharedPtr< SDataObjectListViewRow > RowWidget = StaticCastSharedPtr< SDataObjectListViewRow >(CellsListView->WidgetFromItem(VisibleRows[HighlightedVisibleRowIndex]));
		RowWidget->SetRowForRename();
	}
}

void FEndDataObjectEditor::DeleteSelectedRow()
{
	if (UEndDataObjectBase* DataObject = GetEditableDataObject())
	{
		// We must perform this before removing the row
		const int32 RowToRemoveIndex = VisibleRows.IndexOfByPredicate([&](const FDataObjectEditorRowListViewDataPtr& InRowName) -> bool
			{
				return InRowName->RowId == HighlightedRowName;
			});
		// Remove row
		if (FDataObjectEditorUtils::RemoveRow(DataObject, HighlightedRowName))
		{
			// Try and keep the same row index selected
			const int32 RowIndexToSelect = FMath::Clamp(RowToRemoveIndex, 0, VisibleRows.Num() - 1);
			if (VisibleRows.IsValidIndex(RowIndexToSelect))
			{
				FDataObjectEditorUtils::SelectRow(DataObject, VisibleRows[RowIndexToSelect]->RowId);
			}
			// Refresh list. Otherwise, the removed row would still appear in the screen until the next list refresh. An
			// analog of CellsListView->RequestListRefresh() also occurs inside FDataObjectEditorUtils::SelectRow
			else
			{
				CellsListView->RequestListRefresh();
			}
		}
	}
}

FText FEndDataObjectEditor::GetFilterText() const
{
	return ActiveFilterText;
}

void FEndDataObjectEditor::OnFilterTextChanged(const FText& InFilterText)
{
	ActiveFilterText = InFilterText;
	UpdateVisibleRows();
}

void FEndDataObjectEditor::OnFilterTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo)
{
	if (CommitInfo == ETextCommit::OnCleared)
	{
		SearchBoxWidget->SetText(FText::GetEmpty());
		OnFilterTextChanged(FText::GetEmpty());
	}
}


TSharedRef<SVerticalBox> FEndDataObjectEditor::CreateContentBox()
{
	TSharedRef<SScrollBar> HorizontalScrollBar = SNew(SScrollBar)
		.Orientation(Orient_Horizontal)
		.Thickness(FVector2D(12.0f, 12.0f));

	TSharedRef<SScrollBar> VerticalScrollBar = SNew(SScrollBar)
		.Orientation(Orient_Vertical)
		.Thickness(FVector2D(12.0f, 12.0f));

	ColumnNamesHeaderRow = SNew(SHeaderRow);

	CellsListView = SNew(SListView<FDataObjectEditorRowListViewDataPtr>)
		.ListItemsSource(&VisibleRows)
		.HeaderRow(ColumnNamesHeaderRow)
		.OnGenerateRow(this, &FEndDataObjectEditor::MakeRowWidget)
		.OnSelectionChanged(this, &FEndDataObjectEditor::OnRowSelectionChanged)
		.ExternalScrollbar(VerticalScrollBar)
		.ConsumeMouseWheel(EConsumeMouseWheel::Always)
		.SelectionMode(ESelectionMode::Single)
		.AllowOverscroll(EAllowOverscroll::No);
		

	LoadLayoutData();
	RefreshCachedDataObject();

	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		[
			SAssignNew(SearchBoxWidget, SSearchBox)
			.InitialText(this, &FEndDataObjectEditor::GetFilterText)
		.OnTextChanged(this, &FEndDataObjectEditor::OnFilterTextChanged)
		.OnTextCommitted(this, &FEndDataObjectEditor::OnFilterTextCommitted)
		]
		]
	+ SVerticalBox::Slot()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		[
			SNew(SScrollBox)
			.Orientation(Orient_Horizontal)
		.ExternalScrollbar(HorizontalScrollBar)
		+ SScrollBox::Slot()
		[
			CellsListView.ToSharedRef()
		]
		]
	+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			VerticalScrollBar
		]
		]
	+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		[
			HorizontalScrollBar
		]
		];
}

TSharedRef<SWidget> FEndDataObjectEditor::CreateRowEditorBox()
{
	UEndDataObjectBase* DataObject = Cast<UEndDataObjectBase>(GetEditingObject());

	// Support undo/redo
	if (DataObject)
	{
		DataObject->SetFlags(RF_Transactional);
	}

	auto RowEditor = SNew(SEndRowEditor, DataObject);
	RowEditor->RowSelectedCallback.BindSP(this, &FEndDataObjectEditor::SetHighlightedRow);
	CallbackOnRowHighlighted.BindSP(RowEditor, &SEndRowEditor::SelectRow);
	CallbackOnDataObjectUndoRedo.BindSP(RowEditor, &SEndRowEditor::HandleUndoRedo);
	return RowEditor;
}

TSharedRef<SEndRowEditor> FEndDataObjectEditor::CreateRowEditor(UEndDataObjectBase* Table)
{
	return SNew(SEndRowEditor, Table);
}

TSharedRef<SDockTab> FEndDataObjectEditor::SpawnTab_RowEditor(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId().TabType == RowEditorTabId);

	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("DataObjectEditor.Tabs.Properties"))
		.Label(LOCTEXT("RowEditorTitle", "Row Editor"))
		.TabColorScale(GetTabColorScale())
		[
			SNew(SBorder)
			.Padding(2)
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Fill)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		[
			RowEditorTabWidget.ToSharedRef()
		]
		];
}


TSharedRef<SDockTab> FEndDataObjectEditor::SpawnTab_DataObject(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId().TabType == DataObjectTabId);

	UEndDataObjectBase* DataObject = Cast<UEndDataObjectBase>(GetEditingObject());

	// Support undo/redo
	if (DataObject)
	{
		DataObject->SetFlags(RF_Transactional);
	}

	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("DataObjectEditor.Tabs.Properties"))
		.Label(LOCTEXT("DataObjectTitle", "Data Object"))
		.TabColorScale(GetTabColorScale())
		[
			SNew(SBorder)
			.Padding(2)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		[
			DataObjectTabWidget.ToSharedRef()
		]
		];
}

TSharedRef<SDockTab> FEndDataObjectEditor::SpawnTab_DataObjectDetails(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId().TabType == DataObjectDetailsTabId);

	PropertyView->SetObject(GetEditableDataObject());

	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("DataObjectEditor.Tabs.Properties"))
		.Label(LOCTEXT("DataObjectDetails", "Data Object Details"))
		.TabColorScale(GetTabColorScale())
		[
			SNew(SBorder)
			.Padding(2)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		[
			PropertyView.ToSharedRef()
		]
		];
}

void FEndDataObjectEditor::SetHighlightedRow(FName Name)
{
	if (Name == HighlightedRowName)
	{
		return;
	}

	if (Name.IsNone())
	{
		HighlightedRowName = NAME_None;
		CellsListView->ClearSelection();
		HighlightedVisibleRowIndex = INDEX_NONE;
	}
	else
	{
		HighlightedRowName = Name;

		FDataObjectEditorRowListViewDataPtr* NewSelectionPtr = NULL;
		for (HighlightedVisibleRowIndex = 0; HighlightedVisibleRowIndex < VisibleRows.Num(); ++HighlightedVisibleRowIndex)
		{
			if (VisibleRows[HighlightedVisibleRowIndex]->RowId == Name)
			{
				NewSelectionPtr = &(VisibleRows[HighlightedVisibleRowIndex]);

				break;
			}
		}


		// Synchronize the list views
		if (NewSelectionPtr)
		{
			CellsListView->SetSelection(*NewSelectionPtr);

			CellsListView->RequestScrollIntoView(*NewSelectionPtr);
		}
		else
		{
			CellsListView->ClearSelection();
		}
	}
}

#undef LOCTEXT_NAMESPACE