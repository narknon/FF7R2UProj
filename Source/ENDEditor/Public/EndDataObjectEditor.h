#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "EditorViewportClient.h"
#include "SEditorViewport.h"
#include "SEndRowEditor.h"
#include "EditorUndoClient.h"
#include "EndDataObjectBase.h"
#include "Widgets/Input/SSearchBox.h"
#include "DataObjectEditorUtils.h"

class FJsonObject;

DECLARE_DELEGATE_OneParam(FOnRowHighlighted, FName /*Row name*/);

class FEndDataObjectEditor : public FAssetEditorToolkit
	, public FEditorUndoClient
	//, public FStructureEditorUtils::INotifyOnStructChanged
	//, public FDataObjectEditorUtils::INotifyOnDataObjectChanged
{
	friend class SDataObjectListViewRow;

public:
    /** Constructor */
    FEndDataObjectEditor();

    /** Destructor */
    virtual ~FEndDataObjectEditor();

    virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
    virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;


    // Initializes the asset editor
    void InitEndDataObjectEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UEndDataObjectBase* InEndDataObject);

    virtual bool CanEditRows() const;

    // FAssetEditorToolkit
    virtual FName GetToolkitFName() const override;
    virtual FText GetBaseToolkitName() const override;
    virtual FString GetWorldCentricTabPrefix() const override;
    virtual FLinearColor GetWorldCentricTabColorScale() const override;

    // FEditorUndoClient
    virtual void PostUndo(bool bSuccess) override;
    virtual void PostRedo(bool bSuccess) override;
    void HandleUndoRedo();

    // INotifyOnStructChanged
    //virtual void PreChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info) override;
    //virtual void PostChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info) override;

    // INotifyOnDataTableChanged
    //virtual void PreChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo Info) override;
    //virtual void PostChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo Info) override;
    //virtual void SelectionChange(const UDataTable* Changed, FName RowName) override;

    // Get the asset being edited
	const UEndDataObjectBase* GetDataObject() const;

    void HandlePostChange();

    void SetHighlightedRow(FName Name);

    FText GetFilterText() const;

    FSlateColor GetRowTextColor(FName RowName) const;

protected:
	void RefreshCachedDataObject(const FName InCachedSelection = NAME_None, const bool bUpdateEvenIfValid = false);

	void UpdateVisibleRows(const FName InCachedSelection = NAME_None, const bool bUpdateEvenIfValid = false);

	void RestoreCachedSelection(const FName InCachedSelection, const bool bUpdateEvenIfValid = false);

	void OnFilterTextChanged(const FText& InFilterText);
	void OnFilterTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);

	/*virtual void PostRegenerateMenusAndToolbars() override;

	FReply OnFindRowInContentBrowserClicked();

	void OnNavigateToDataTableRowCode();*/

	FText GetCellText(FDataObjectEditorRowListViewDataPtr InRowDataPointer, int32 ColumnIndex) const;
	FText GetCellToolTipText(FDataObjectEditorRowListViewDataPtr InRowDataPointer, int32 ColumnIndex) const;

	TSharedRef<SVerticalBox> CreateContentBox();

	TSharedRef<SWidget> CreateRowEditorBox();
	virtual TSharedRef<SEndRowEditor> CreateRowEditor(UEndDataObjectBase* Table);

	/**	Spawns the tab with the data object inside */
	TSharedRef<SDockTab> SpawnTab_DataObject(const FSpawnTabArgs& Args);

	/**	Spawns the tab with the data object inside */
	TSharedRef<SDockTab> SpawnTab_DataObjectDetails(const FSpawnTabArgs& Args);

	/**	Spawns the tab with the Row Editor inside */
	TSharedRef<SDockTab> SpawnTab_RowEditor(const FSpawnTabArgs& Args);

	float GetRowNameColumnWidth() const;
	void RefreshRowNameColumnWidth();

	float GetRowNumberColumnWidth() const;
	void RefreshRowNumberColumnWidth();

	float GetColumnWidth(const int32 ColumnIndex) const;

	void OnColumnResized(const float NewWidth, const int32 ColumnIndex);

	void OnRowNameColumnResized(const float NewWidth);

	void OnRowNumberColumnResized(const float NewWidth);

	void LoadLayoutData();

	void SaveLayoutData();

	/** Make the widget for a row entry in the data object row list view */
	TSharedRef<ITableRow> MakeRowWidget(FDataObjectEditorRowListViewDataPtr InRowDataPtr, const TSharedRef<STableViewBase>& OwnerTable);

	/** Make the widget for a cell entry in the data object row list view */
	TSharedRef<SWidget> MakeCellWidget(FDataObjectEditorRowListViewDataPtr InRowDataPtr, const int32 InRowIndex, const FName& InColumnId);

	void OnRowSelectionChanged(FDataObjectEditorRowListViewDataPtr InNewSelection, ESelectInfo::Type InSelectInfo);

	void CopySelectedRow();
	void PasteOnSelectedRow();
	void DuplicateSelectedRow();
	void RenameSelectedRowCommand();
	void DeleteSelectedRow();

	/** Helper function for creating and registering the tab containing the data object data */
	virtual void CreateAndRegisterDataObjectTab(const TSharedRef<class FTabManager>& InTabManager);

	/** Helper function for creating and registering the tab containing the data object details */
	virtual void CreateAndRegisterDataObjectDetailsTab(const TSharedRef<class FTabManager>& InTabManager);

	/** Helper function for creating and registering the tab containing the row editor */
	virtual void CreateAndRegisterRowEditorTab(const TSharedRef<class FTabManager>& InTabManager);

	virtual FString GetDocumentationLink() const override;

	void OnAddClicked();
	void OnRemoveClicked();
	FReply OnMoveRowClicked(FDataObjectEditorUtils::ERowMoveDirection MoveDirection);
	FReply OnMoveToExtentClicked(FDataObjectEditorUtils::ERowMoveDirection MoveDirection);
	void OnCopyClicked();
	void OnPasteClicked();
	void OnDuplicateClicked();

	void SetDefaultSort();
	EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;
	/*void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);
	void OnColumnNumberSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);
	void OnColumnNameSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);

	void OnEditDataObjectStructClicked();*/

    void ExtendToolbar(TSharedPtr<FExtender> Extender);
    void FillToolbar(FToolBarBuilder& ToolbarBuilder);

private:
	UEndDataObjectBase* GetEditableDataObject() const;

//protected:
public:
    TSharedRef<SDockTab> SpawnPropertiesTab(const FSpawnTabArgs& Args);
    TSharedRef<SDockTab> SpawnRowMapTab(const FSpawnTabArgs& Args);

    // The data object asset being edited
    UEndDataObjectBase* EndDataObject;

	/** Struct holding information about the current column widths */
	struct FColumnWidth
	{
		FColumnWidth()
			: bIsAutoSized(true)
			, CurrentWidth(0.0f)
		{
		}

		/** True if this column is being auto-sized rather than sized by the user */
		bool bIsAutoSized;
		/** The width of the column, either sized by the user, or auto-sized */
		float CurrentWidth;
	};

	/** UI for the "Data Object" tab */
	TSharedPtr<SWidget> DataObjectTabWidget;

	/** Property viewing widget */
	TSharedPtr<class IDetailsView> PropertyView;

	/** UI for the "Row Editor" tab */
	TSharedPtr<SSearchBox> SearchBoxWidget;

	/** UI for the "Row Editor" tab */
	TSharedPtr<SWidget> RowEditorTabWidget;

	/** Array of the columns that are available for editing */
	TArray<FDataObjectEditorColumnHeaderDataPtr> AvailableColumns;

	/** Array of the rows that are available for editing */
	TArray<FDataObjectEditorRowListViewDataPtr> AvailableRows;

	/** Array of the rows that match the active filter(s) */
	TArray<FDataObjectEditorRowListViewDataPtr> VisibleRows;

	/** Header row containing entries for each column in AvailableColumns */
	TSharedPtr<SHeaderRow> ColumnNamesHeaderRow;

	/** List view responsible for showing the rows in VisibleRows for each entry in AvailableColumns */
	TSharedPtr<SListView<FDataObjectEditorRowListViewDataPtr>> CellsListView;

	/** Width of the row name column */
	float RowNameColumnWidth;

	/** Width of the row number column */
	float RowNumberColumnWidth;

	/** Widths of data table cell columns */
	TArray<FColumnWidth> ColumnWidths;

	/** The layout data for the currently loaded data object */
	TSharedPtr<FJsonObject> LayoutData;

	/** The name of the currently selected row */
	FName HighlightedRowName;

	/** The visible row index of the currently selected row */
	int32 HighlightedVisibleRowIndex;

	/** The current filter text applied to the data object */
	FText ActiveFilterText;

	/** Currently selected sorting mode */
	EColumnSortMode::Type SortMode;

	/** Specify which column to sort with */
	FName SortByColumn;

	FOnRowHighlighted CallbackOnRowHighlighted;

	FSimpleDelegate CallbackOnDataObjectUndoRedo;

	/**	The tab id for the data object tab */
	static const FName DataObjectTabId;

	/**	The tab id for the data object details tab */
	static const FName DataObjectDetailsTabId;

	/**	The tab id for the row editor tab */
	static const FName RowEditorTabId;

	/** The column id for the row name list view column */
	static const FName RowNameColumnId;

	/** The column id for the row number list view column */
	static const FName RowNumberColumnId;

	/** The column id for the drag drop column */
	static const FName RowDragDropColumnId;
};