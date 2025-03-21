// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "EndDataObjectBase.h"
#include "Kismet2/ListenerManager.h"
#include "Widgets/SWidget.h"
#include "Framework/Commands/UIAction.h"
#include "AssetData.h"

struct FDataObjectEditorColumnHeaderData
{
	/** Unique ID used to identify this column */
	FName ColumnId;

	/** Display name of this column */
	FText DisplayName;

	/** The calculated width of this column taking into account the cell data for each row */
	float DesiredColumnWidth;

	/** The FProperty for the variable in this column */
	const FProperty* Property;
};

struct FDataObjectEditorRowListViewData
{
	/** Unique ID used to identify this row */
	FName RowId;

	/** Display name of this row */
	FText DisplayName;

	/** The calculated height of this row taking into account the cell data for each column */
	float DesiredRowHeight;

	/** Insertion number of the row */
	uint32 RowNum;

	/** Array corresponding to each cell in this row */
	TArray<FText> CellData;
};

enum class ERowInsertionPos
{
	Above,
	Below,
	Bottom,
};

typedef TSharedPtr<FDataObjectEditorColumnHeaderData> FDataObjectEditorColumnHeaderDataPtr;
typedef TSharedPtr<FDataObjectEditorRowListViewData>  FDataObjectEditorRowListViewDataPtr;

struct ENDEDITOR_API FDataObjectEditorUtils
{
	enum class EDataObjectChangeInfo
	{
		/** The data corresponding to a single row has been changed */
		RowData,
		/** The data corresponding to the entire list of rows has been changed */
		RowList,
	};

	enum class ERowMoveDirection
	{
		Up,
		Down,
	};

	class FDataObjectEditorManager : public FListenerManager < UEndDataObjectBase, EDataObjectChangeInfo >
	{
		FDataObjectEditorManager() {}
	public:
		ENDEDITOR_API static FDataObjectEditorManager& Get();

		class ENDEDITOR_API ListenerType : public InnerListenerType<FDataObjectEditorManager>
		{
		public:
			virtual void SelectionChange(const UEndDataObjectBase* DataObject, FName RowName) { }
		};
	};

	typedef FDataObjectEditorManager::ListenerType INotifyOnDataObjectChanged;

	static bool RemoveRow(UEndDataObjectBase* DataObject, FName Name);
	static uint8* AddRow(UEndDataObjectBase* DataObject, FName RowName);
	static uint8* DuplicateRow(UEndDataObjectBase* DataObject, FName SourceRowName, FName RowName);
	static bool RenameRow(UEndDataObjectBase* DataObject, FName OldName, FName NewName);
	static bool MoveRow(UEndDataObjectBase* DataObject, FName RowName, ERowMoveDirection Direction, int32 NumRowsToMoveBy = 1);
	static bool SelectRow(const UEndDataObjectBase* DataObject, FName RowName);
	static bool DiffersFromDefault(UEndDataObjectBase* DataObject, FName RowName);
	static bool ResetToDefault(UEndDataObjectBase* DataObject, FName RowName);

	static uint8* AddRowAboveOrBelowSelection(UEndDataObjectBase* DataObject, const FName& RowName, const FName& NewRowName, ERowInsertionPos InsertPosition);

	static void BroadcastPreChange(UEndDataObjectBase* DataObject, EDataObjectChangeInfo Info);
	static void BroadcastPostChange(UEndDataObjectBase* DataObject, EDataObjectChangeInfo Info);

	/** Reads a data table and parses out editable copies of rows and columns */
	static void CacheDataObjectForEditing(const UEndDataObjectBase* DataObject, TArray<FDataObjectEditorColumnHeaderDataPtr>& OutAvailableColumns, TArray<FDataObjectEditorRowListViewDataPtr>& OutAvailableRows);

	/** Generic version that works with any datatable-like structure */
	static void CacheDataForEditing(const UScriptStruct* RowStruct, const TMap<FName, uint8*>& RowMap, TArray<FDataObjectEditorColumnHeaderDataPtr>& OutAvailableColumns, TArray<FDataObjectEditorRowListViewDataPtr>& OutAvailableRows);

	/** Returns all script structs that can be used as a data table row. This only includes loaded ones */
	static TArray<UScriptStruct*> GetPossibleStructs();

	/** Fills in an array with all possible DataTable structs, unloaded and loaded */
	static void GetPossibleStructAssetData(TArray<FAssetData>& StructAssets);

	/** Utility function which verifies that the specified struct type is viable for data tables */
	static bool IsValidTableStruct(const UScriptStruct* Struct);

	/** Add a UI action for search for references, useful for customizations */
	static void AddSearchForReferencesContextMenu(class FDetailWidgetRow& RowNameDetailWidget, FExecuteAction SearchForReferencesAction);

	/** Short description for a data or curve handle */
	static FText GetHandleShortDescription(const UObject* TableAsset, FName RowName);

	/** Tooltip text for the data table row type */
	static FText GetRowTypeInfoTooltipText(FDataObjectEditorColumnHeaderDataPtr ColumnHeaderDataPtr);

	/** Doc excerpt name for the data table row type */
	static FString GetRowTypeTooltipDocExcerptName(FDataObjectEditorColumnHeaderDataPtr ColumnHeaderDataPtr);

	/** Link to variable type doc  */
	static const FString VariableTypesTooltipDocLink;

	/** Delegate called when a data table struct is selected */
	DECLARE_DELEGATE_OneParam(FOnDataObjectStructSelected, UScriptStruct*);

	/** Creates a combo box that allows selecting from the list of possible row structures */
	static TSharedRef<SWidget> MakeRowStructureComboBox(FOnDataObjectStructSelected OnSelected);
};
