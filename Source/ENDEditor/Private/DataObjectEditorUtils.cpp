// Copyright Epic Games, Inc. All Rights Reserved.

#include "DataObjectEditorUtils.h"
#include "UObject/UObjectHash.h"
#include "UObject/UObjectIterator.h"
#include "Styling/SlateTypes.h"
#include "Fonts/FontMeasure.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Application/SlateUser.h"
#include "EditorStyleSet.h"
#include "Engine/UserDefinedStruct.h"
#include "Misc/StringUtility.h"
#include "ScopedTransaction.h"
#include "K2Node_GetDataTableRow.h"
#include "Input/Reply.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Input/SComboBox.h"
#include "AssetRegistryModule.h"
#include "DetailWidgetRow.h"
#include "Editor.h"

#define LOCTEXT_NAMESPACE "DataObjectEditorUtils"

/** Combobox that allows selecting a struct row for a data table. Based off of SSearchableComboBox */
class SDataObjectStructComboBox : public SComboButton
{
public:
	/** Type of list used for showing menu options. */
	typedef SListView< TSharedPtr<FString> > SComboListType;
	/** Delegate type used to generate widgets that represent Options */
	typedef typename TSlateDelegates< TSharedPtr<FString> >::FOnGenerateWidget FOnGenerateWidget;
	typedef typename TSlateDelegates< TSharedPtr<FString> >::FOnSelectionChanged FOnSelectionChanged;
	DECLARE_DELEGATE_OneParam(FOnFillComboBoxStrings, TArray<TSharedPtr<FString>>&);

	SLATE_BEGIN_ARGS(SDataObjectStructComboBox)
		: _Content()
		, _ComboBoxStyle(&FCoreStyle::Get().GetWidgetStyle< FComboBoxStyle >("ComboBox"))
		, _ButtonStyle(nullptr)
		, _ItemStyle(&FCoreStyle::Get().GetWidgetStyle< FTableRowStyle >("TableView.Row"))
		, _ContentPadding(FMargin(4.0, 2.0))
		, _ForegroundColor(FCoreStyle::Get().GetSlateColor("InvertedForeground"))
		, _OnStructSelected()
		, _InitiallySelectedItem(nullptr)
		, _Method()
		, _MaxListHeight(450.0f)
		, _HasDownArrow(true)
	{}

	/** Slot for this button's content (optional) */
	SLATE_DEFAULT_SLOT(FArguments, Content)

		SLATE_STYLE_ARGUMENT(FComboBoxStyle, ComboBoxStyle)

		/** The visual style of the button part of the combo box (overrides ComboBoxStyle) */
		SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle)

		SLATE_STYLE_ARGUMENT(FTableRowStyle, ItemStyle)

		SLATE_ATTRIBUTE(FMargin, ContentPadding)
		SLATE_ATTRIBUTE(FSlateColor, ForegroundColor)

		SLATE_EVENT(FDataObjectEditorUtils::FOnDataObjectStructSelected, OnStructSelected)

		/** The custom scrollbar to use in the ListView */
		SLATE_ARGUMENT(TSharedPtr<SScrollBar>, CustomScrollbar)

		/** The option that should be selected when the combo box is first created */
		SLATE_ARGUMENT(TSharedPtr<FString>, InitiallySelectedItem)

		SLATE_ARGUMENT(TOptional<EPopupMethod>, Method)

		/** The max height of the combo box menu */
		SLATE_ARGUMENT(float, MaxListHeight)

		/**
		 * When false, the down arrow is not generated and it is up to the API consumer
		 * to make their own visual hint that this is a drop down.
		 */
		SLATE_ARGUMENT(bool, HasDownArrow)

		SLATE_END_ARGS()

		/**
		 * Construct the widget from a declaration
		 *
		 * @param InArgs   Declaration from which to construct the combo box
		 */
		void Construct(const FArguments& InArgs);

	void ClearSelection();

	void SetSelectedItem(TSharedPtr<FString> InSelectedItem);

	/** @return the item currently selected by the combo box. */
	TSharedPtr<FString> GetSelectedItem();

	/**
	 * Requests a list refresh after updating options
	 * Call SetSelectedItem to update the selected item if required
	 * @see SetSelectedItem
	 */
	void RefreshOptions();

	/** Returns the asset data for a specific string, or null if not found */
	const FAssetData* FindAssetDataForString(TSharedPtr<FString> StringOption) const;

	/** Returns struct from AssetData, possibly loading it */
	UScriptStruct* GetOrLoadStruct(const FAssetData* AssetData);

private:

	/** Generate a row for the InItem in the combo box's list (passed in as OwnerTable). Do this by calling the user-specified OnGenerateWidget */
	TSharedRef<ITableRow> GenerateMenuItemRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);

	/** Called if the menu is closed */
	void OnMenuOpenChanged(bool bOpen);

	/** Invoked when the selection in the list changes */
	void OnSelectionChanged_Internal(TSharedPtr<FString> ProposedSelection, ESelectInfo::Type SelectInfo);

	/** Invoked when the search text changes */
	void OnSearchTextChanged(const FText& ChangedText);

	/** Text to display inside box */
	FText GetSelectedText() const;

	/** Show tooltip text for a specific option */
	FText GetTooltipText(TSharedPtr<FString> StringOption);

	/** Handle clicking on the content menu */
	virtual FReply OnButtonClicked() override;

	/** The item style to use. */
	const FTableRowStyle* ItemStyle;

private:
	/** Delegate that is invoked when the selected item in the combo box changes */
	FDataObjectEditorUtils::FOnDataObjectStructSelected OnStructSelected;

	/** The item currently selected in the combo box */
	TSharedPtr<FString> SelectedItem;
	/** The search field used for the combox box's contents */
	TSharedPtr< SEditableTextBox > SearchField;
	/** The ListView that we pop up; visualized the available options. */
	TSharedPtr< SComboListType > ComboListView;
	/** The Scrollbar used in the ListView. */
	TSharedPtr< SScrollBar > CustomScrollbar;

	/** List of names to show in combo box, there is a 1:1 mapping to PossibleStructs */
	TArray< TSharedPtr<FString> > CurrentOptions;
	/** List of AssetData representing rows */
	TArray<FAssetData> PossibleStructs;
};

void SDataObjectStructComboBox::Construct(const FArguments& InArgs)
{
	check(InArgs._ComboBoxStyle);

	ItemStyle = InArgs._ItemStyle;

	// Work out which values we should use based on whether we were given an override, or should use the style's version
	const FComboButtonStyle& OurComboButtonStyle = InArgs._ComboBoxStyle->ComboButtonStyle;
	const FButtonStyle* const OurButtonStyle = InArgs._ButtonStyle ? InArgs._ButtonStyle : &OurComboButtonStyle.ButtonStyle;

	this->OnStructSelected = InArgs._OnStructSelected;

	CustomScrollbar = InArgs._CustomScrollbar;

	TSharedRef<SWidget> ComboBoxMenuContent =
		SNew(SBox)
		.MaxDesiredHeight(InArgs._MaxListHeight)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(this->SearchField, SEditableTextBox)
			.HintText(LOCTEXT("Search", "Search"))
		.OnTextChanged(this, &SDataObjectStructComboBox::OnSearchTextChanged)
		]

	+ SVerticalBox::Slot()
		[
			SAssignNew(this->ComboListView, SComboListType)
			.ListItemsSource(&CurrentOptions)
		.OnGenerateRow(this, &SDataObjectStructComboBox::GenerateMenuItemRow)
		.OnSelectionChanged(this, &SDataObjectStructComboBox::OnSelectionChanged_Internal)
		.SelectionMode(ESelectionMode::Single)
		.ExternalScrollbar(InArgs._CustomScrollbar)
		]
		];

	// Set up content
	TSharedPtr<SWidget> ButtonContent = InArgs._Content.Widget;
	if (InArgs._Content.Widget == SNullWidget::NullWidget)
	{
		SAssignNew(ButtonContent, STextBlock)
			.Text(this, &SDataObjectStructComboBox::GetSelectedText);
	}

	SComboButton::Construct(SComboButton::FArguments()
		.ComboButtonStyle(&OurComboButtonStyle)
		.ButtonStyle(OurButtonStyle)
		.Method(InArgs._Method)
		.ButtonContent()
		[
			ButtonContent.ToSharedRef()
		]
	.MenuContent()
		[
			ComboBoxMenuContent
		]
	.HasDownArrow(InArgs._HasDownArrow)
		.ContentPadding(InArgs._ContentPadding)
		.ForegroundColor(InArgs._ForegroundColor)
		.OnMenuOpenChanged(this, &SDataObjectStructComboBox::OnMenuOpenChanged)
		.IsFocusable(true)
		);

	// Better to select search field so you can type right away
	SetMenuContentWidgetToFocus(SearchField);

	// Refresh options now
	RefreshOptions();

	// Need to establish the selected item at point of construction so its available for querying
	// NB: If you need a selection to fire use SetItemSelection rather than setting an IntiallySelectedItem
	SelectedItem = InArgs._InitiallySelectedItem;
	if (TListTypeTraits<TSharedPtr<FString>>::IsPtrValid(SelectedItem))
	{
		ComboListView->Private_SetItemSelection(SelectedItem, true);
	}
}

void SDataObjectStructComboBox::ClearSelection()
{
	ComboListView->ClearSelection();
}

void SDataObjectStructComboBox::SetSelectedItem(TSharedPtr<FString> InSelectedItem)
{
	if (TListTypeTraits<TSharedPtr<FString>>::IsPtrValid(InSelectedItem))
	{
		ComboListView->SetSelection(InSelectedItem);
	}
	else
	{
		ComboListView->ClearSelection();
	}
}

TSharedPtr<FString> SDataObjectStructComboBox::GetSelectedItem()
{
	return SelectedItem;
}

FText SDataObjectStructComboBox::GetSelectedText() const
{
	if (SelectedItem.IsValid())
	{
		return FText::FromString(*SelectedItem);
	}

	return FText::GetEmpty();
}

FText SDataObjectStructComboBox::GetTooltipText(TSharedPtr<FString> StringOption)
{
	const FAssetData* FoundAsset = FindAssetDataForString(StringOption);

	if (FoundAsset)
	{
		return FText::FromString(FoundAsset->PackageName.ToString());
	}
	return FText::GetEmpty();
}

void SDataObjectStructComboBox::RefreshOptions()
{
	if (PossibleStructs.Num() == 0)
	{
		FDataObjectEditorUtils::GetPossibleStructAssetData(PossibleStructs);

		CurrentOptions.Reset();
		for (const FAssetData& FoundStruct : PossibleStructs)
		{
			CurrentOptions.Add(MakeShareable(new FString(FoundStruct.AssetName.ToString())));
		}
	}

	if (!ComboListView->IsPendingRefresh())
	{
		ComboListView->RequestListRefresh();
	}
}

const FAssetData* SDataObjectStructComboBox::FindAssetDataForString(TSharedPtr<FString> StringOption) const
{
	check(CurrentOptions.Num() == PossibleStructs.Num());
	for (int32 i = 0; i < CurrentOptions.Num(); i++)
	{
		if (StringOption == CurrentOptions[i])
		{
			return &PossibleStructs[i];
		}
	}
	return nullptr;
}

UScriptStruct* SDataObjectStructComboBox::GetOrLoadStruct(const FAssetData* AssetData)
{
	if (!AssetData)
	{
		return nullptr;
	}

	return Cast<UScriptStruct>(AssetData->GetAsset());
}

TSharedRef<ITableRow> SDataObjectStructComboBox::GenerateMenuItemRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	FString SearchToken = SearchField->GetText().ToString().ToLower();
	EVisibility WidgetVisibility = EVisibility::Visible;
	if (!SearchToken.IsEmpty())
	{
		if (InItem->ToLower().Find(SearchToken) < 0)
		{
			WidgetVisibility = EVisibility::Collapsed;
		}
	}

	TAttribute<FText> OnGetToolTip = TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateSP(this, &SDataObjectStructComboBox::GetTooltipText, InItem));

	return SNew(SComboRow<TSharedPtr<FString>>, OwnerTable)
		.Style(ItemStyle)
		.Visibility(WidgetVisibility)
		[
			SNew(STextBlock)
			.Text(FText::FromString(*InItem))
		.ToolTipText(OnGetToolTip)
		];
}

void SDataObjectStructComboBox::OnMenuOpenChanged(bool bOpen)
{
	if (bOpen == false)
	{
		if (TListTypeTraits<TSharedPtr<FString>>::IsPtrValid(SelectedItem))
		{
			// Ensure the ListView selection is set back to the last committed selection
			ComboListView->SetSelection(SelectedItem, ESelectInfo::OnNavigation);
			ComboListView->RequestScrollIntoView(SelectedItem, 0);
		}

		// Set focus back to ComboBox for users focusing the ListView that just closed
		TSharedRef<SWidget> ThisRef = AsShared();
		FSlateApplication::Get().ForEachUser([&ThisRef](FSlateUser& User) {
			if (User.HasFocusedDescendants(ThisRef))
			{
				User.SetFocus(ThisRef, EFocusCause::SetDirectly);
			}
			});
	}
}

void SDataObjectStructComboBox::OnSelectionChanged_Internal(TSharedPtr<FString> ProposedSelection, ESelectInfo::Type SelectInfo)
{
	// Ensure that the proposed selection is different
	if (SelectInfo != ESelectInfo::OnNavigation)
	{
		// Ensure that the proposed selection is different from selected
		if (ProposedSelection != SelectedItem)
		{
			SelectedItem = ProposedSelection;

			UScriptStruct* SelectedStruct = GetOrLoadStruct(FindAssetDataForString(SelectedItem));

			OnStructSelected.ExecuteIfBound(SelectedStruct);

		}
		// close combo even if user reselected item
		this->SetIsOpen(false);
	}
}

void SDataObjectStructComboBox::OnSearchTextChanged(const FText& ChangedText)
{
	FString SearchToken = ChangedText.ToString().ToLower();
	for (int32 i = 0; i < CurrentOptions.Num(); i++)
	{
		TSharedPtr<ITableRow> Row = ComboListView->WidgetFromItem(CurrentOptions[i]);
		if (Row)
		{
			if (SearchToken.IsEmpty())
			{
				Row->AsWidget()->SetVisibility(EVisibility::Visible);
			}
			else if (CurrentOptions[i]->ToLower().Find(SearchToken) >= 0)
			{
				Row->AsWidget()->SetVisibility(EVisibility::Visible);
			}
			else
			{
				Row->AsWidget()->SetVisibility(EVisibility::Collapsed);
			}
		}
	}

	ComboListView->RequestListRefresh();

	SelectedItem = TSharedPtr< FString >();
}

FReply SDataObjectStructComboBox::OnButtonClicked()
{
	// if user clicked to close the combo menu
	if (this->IsOpen())
	{
		// Re-select first selected item, just in case it was selected by navigation previously
		TArray<TSharedPtr<FString>> SelectedItems = ComboListView->GetSelectedItems();
		if (SelectedItems.Num() > 0)
		{
			OnSelectionChanged_Internal(SelectedItems[0], ESelectInfo::Direct);
		}
	}
	else
	{
		SearchField->SetText(FText::GetEmpty());
		RefreshOptions();
	}

	return SComboButton::OnButtonClicked();
}

const FString FDataObjectEditorUtils::VariableTypesTooltipDocLink = TEXT("Shared/Editor/Blueprint/VariableTypes");

TSharedRef<SWidget> FDataObjectEditorUtils::MakeRowStructureComboBox(FOnDataObjectStructSelected OnSelected)
{
	TSharedRef<SDataObjectStructComboBox> ComboBox = SNew(SDataObjectStructComboBox)
		.OnStructSelected(OnSelected)
		.ContentPadding(3);

	return ComboBox;
}

FDataObjectEditorUtils::FDataObjectEditorManager& FDataObjectEditorUtils::FDataObjectEditorManager::Get()
{
	static TSharedRef< FDataObjectEditorManager > EditorManager(new FDataObjectEditorManager());
	return *EditorManager;
}

bool FDataObjectEditorUtils::RemoveRow(UEndDataObjectBase* DataObject, FName Name)
{
	bool bResult = false;
	if (DataObject && DataObject->RowStruct)
	{
		const FScopedTransaction Transaction(LOCTEXT("RemoveDataObjectRow", "Remove Data Object Row"));

		BroadcastPreChange(DataObject, EDataObjectChangeInfo::RowList);
		DataObject->Modify();
		uint8* RowData = nullptr;
		const bool bRemoved = DataObject->GetNonConstRowMap().RemoveAndCopyValue(Name, RowData);
		if (bRemoved && RowData)
		{
			DataObject->RowStruct->DestroyStruct(RowData);
			FMemory::Free(RowData);
			bResult = true;

			// Compact the map so that a subsequent add goes at the end of the table
			DataObject->GetNonConstRowMap().CompactStable();
		}
		BroadcastPostChange(DataObject, EDataObjectChangeInfo::RowList);
	}
	return bResult;
}

uint8* FDataObjectEditorUtils::AddRow(UEndDataObjectBase* DataObject, FName RowName)
{
	if (!DataObject || (RowName == NAME_None) || (DataObject->GetRowMap().Find(RowName) != nullptr) || !DataObject->RowStruct)
	{
		return nullptr;
	}

	const FScopedTransaction Transaction(LOCTEXT("AddDataObjectRow", "Add Data Object Row"));

	BroadcastPreChange(DataObject, EDataObjectChangeInfo::RowList);
	DataObject->Modify();
	// Allocate data to store information, using UScriptStruct to know its size
	uint8* RowData = (uint8*)FMemory::Malloc(DataObject->RowStruct->GetStructureSize());
	DataObject->RowStruct->InitializeStruct(RowData);
	// And be sure to call DestroyScriptStruct later

	// Add to row map
	DataObject->AddRowInternal(RowName, RowData);
	BroadcastPostChange(DataObject, EDataObjectChangeInfo::RowList);
	return RowData;
}

uint8* FDataObjectEditorUtils::AddRowAboveOrBelowSelection(UEndDataObjectBase* DataObject, const FName& RowName, const FName& NewRowName, ERowInsertionPos InsertPosition)
{
	if (!DataObject || (NewRowName == NAME_None) || (DataObject->GetRowMap().Find(NewRowName) != nullptr) || !DataObject->RowStruct)
	{
		return nullptr;
	}

	const FScopedTransaction Transaction(LOCTEXT("AddDataObjectRowAboveBelow", "Add Data Object Row Above or Below"));

	TArray<FName> OrderedRowNames;
	DataObject->GetRowMap().GenerateKeyArray(OrderedRowNames);

	int32 CurrentRowIndex = OrderedRowNames.IndexOfByKey(RowName);
	if (CurrentRowIndex == INDEX_NONE)
	{
		return nullptr;
	}

	if (InsertPosition == ERowInsertionPos::Below)
	{
		CurrentRowIndex += 1;
	}

	OrderedRowNames.Insert(NewRowName, CurrentRowIndex);

	// Build a name -> index map as the KeySort will hit this a lot
	TMap<FName, int32> NamesToNewIndex;
	for (int32 NameIndex = 0; NameIndex < OrderedRowNames.Num(); ++NameIndex)
	{
		NamesToNewIndex.Add(OrderedRowNames[NameIndex], NameIndex);
	}


	BroadcastPreChange(DataObject, EDataObjectChangeInfo::RowList);

	DataObject->Modify();

	// Allocate data to store information, using UScriptStruct to know its size
	uint8* RowData = (uint8*)FMemory::Malloc(DataObject->RowStruct->GetStructureSize());

	// And be sure to call DestroyScriptStruct later
	DataObject->RowStruct->InitializeStruct(RowData);

	// Add to row map
	DataObject->AddRowInternal(NewRowName, RowData);

	// Re-sort the map keys to match the new order
	DataObject->GetNonConstRowMap().KeySort([&NamesToNewIndex](const FName& One, const FName& Two) -> bool
		{
			const int32 OneIndex = NamesToNewIndex.FindRef(One);
			const int32 TwoIndex = NamesToNewIndex.FindRef(Two);
			return OneIndex < TwoIndex;
		});

	BroadcastPostChange(DataObject, EDataObjectChangeInfo::RowList);

	return RowData;
}


uint8* FDataObjectEditorUtils::DuplicateRow(UEndDataObjectBase* DataObject, FName SourceRowName, FName RowName)
{
	if (!DataObject || (SourceRowName == NAME_None) || !DataObject->RowMap.Contains(SourceRowName) || DataObject->RowMap.Contains(RowName) || !DataObject->RowStruct)
	{
		return NULL;
	}

	const FScopedTransaction Transaction(LOCTEXT("DuplicateDataObjectRow", "Duplicate Data Object Row"));

	BroadcastPreChange(DataObject, EDataObjectChangeInfo::RowList);
	DataObject->Modify();

	// Allocate data to store information, using UScriptStruct to know its size
	uint8* OldRowData = *DataObject->RowMap.Find(SourceRowName);
	uint8* NewRowData = (uint8*)FMemory::Malloc(DataObject->RowStruct->GetStructureSize());

	DataObject->RowStruct->InitializeStruct(NewRowData);
	DataObject->RowStruct->CopyScriptStruct(NewRowData, OldRowData);

	// Add to row map
	DataObject->RowMap.Add(RowName, NewRowData);
	BroadcastPostChange(DataObject, EDataObjectChangeInfo::RowList);
	return NewRowData;
}

bool FDataObjectEditorUtils::RenameRow(UEndDataObjectBase* DataObject, FName OldName, FName NewName)
{
	bool bResult = false;
	if (DataObject)
	{
		const FScopedTransaction Transaction(LOCTEXT("RenameDataObjectRow", "Rename Data Object Row"));

		BroadcastPreChange(DataObject, EDataObjectChangeInfo::RowList);
		DataObject->Modify();

		uint8* RowData = nullptr;
		const bool bValidnewName = (NewName != NAME_None) && !DataObject->GetRowMap().Find(NewName);
		const bool bRemoved = bValidnewName && DataObject->GetNonConstRowMap().RemoveAndCopyValue(OldName, RowData);
		if (bRemoved)
		{
			DataObject->GetNonConstRowMap().FindOrAdd(NewName) = RowData;
			bResult = true;
		}
		BroadcastPostChange(DataObject, EDataObjectChangeInfo::RowList);
	}
	return bResult;
}

bool FDataObjectEditorUtils::MoveRow(UEndDataObjectBase* DataObject, FName RowName, ERowMoveDirection Direction, int32 NumRowsToMoveBy)
{
	if (!DataObject)
	{
		return false;
	}

	// Our maps are ordered which is why we can get away with this
	// If we ever change our map implementation, we'll need to preserve this order information in a separate array and 
	// make sure that order dependent code (such as exporting and the data table viewer) use that when dealing with rows
	// This may also require making RowMap private and fixing up all the existing code that references it directly
	TArray<FName> OrderedRowNames;
	DataObject->GetRowMap().GenerateKeyArray(OrderedRowNames);

	const int32 CurrentRowIndex = OrderedRowNames.IndexOfByKey(RowName);
	if (CurrentRowIndex == INDEX_NONE)
	{
		return false;
	}

	// Calculate our new row index, clamped to the available rows
	int32 NewRowIndex = INDEX_NONE;
	switch (Direction)
	{
	case ERowMoveDirection::Up:
		NewRowIndex = FMath::Clamp(CurrentRowIndex - NumRowsToMoveBy, 0, OrderedRowNames.Num() - 1);
		break;

	case ERowMoveDirection::Down:
		NewRowIndex = FMath::Clamp(CurrentRowIndex + NumRowsToMoveBy, 0, OrderedRowNames.Num() - 1);
		break;

	default:
		break;
	}

	if (NewRowIndex == INDEX_NONE)
	{
		return false;
	}

	if (CurrentRowIndex == NewRowIndex)
	{
		// Nothing to do, but not an error
		return true;
	}

	// Swap the order around as requested
	OrderedRowNames.RemoveAt(CurrentRowIndex, 1, false);
	OrderedRowNames.Insert(RowName, NewRowIndex);

	// Build a name -> index map as the KeySort will hit this a lot
	TMap<FName, int32> NamesToNewIndex;
	for (int32 NameIndex = 0; NameIndex < OrderedRowNames.Num(); ++NameIndex)
	{
		NamesToNewIndex.Add(OrderedRowNames[NameIndex], NameIndex);
	}

	const FScopedTransaction Transaction(LOCTEXT("MoveDataObjectRow", "Move Data Object Row"));

	BroadcastPreChange(DataObject, EDataObjectChangeInfo::RowList);
	DataObject->Modify();

	// Re-sort the map keys to match the new order
	DataObject->GetNonConstRowMap().KeySort([&NamesToNewIndex](const FName& One, const FName& Two) -> bool
		{
			const int32 OneIndex = NamesToNewIndex.FindRef(One);
			const int32 TwoIndex = NamesToNewIndex.FindRef(Two);
			return OneIndex < TwoIndex;
		});

	BroadcastPostChange(DataObject, EDataObjectChangeInfo::RowList);

	return true;
}

bool FDataObjectEditorUtils::SelectRow(const UEndDataObjectBase* DataObject, FName RowName)
{
	for (auto Listener : FDataObjectEditorManager::Get().GetListeners())
	{
		static_cast<INotifyOnDataObjectChanged*>(Listener)->SelectionChange(DataObject, RowName);
	}
	return true;
}

bool FDataObjectEditorUtils::DiffersFromDefault(UEndDataObjectBase* DataObject, FName RowName)
{
	bool bDiffers = false;

	if (DataObject && DataObject->GetRowMap().Contains(RowName))
	{
		uint8* RowData = DataObject->GetRowMap()[RowName];

		if (const UUserDefinedStruct* UDStruct = Cast<const UUserDefinedStruct>(DataObject->RowStruct))
		{
			return !UDStruct->CompareScriptStruct(RowData, UDStruct->GetDefaultInstance(), PPF_None);
		}
	}

	return bDiffers;
}

bool FDataObjectEditorUtils::ResetToDefault(UEndDataObjectBase* DataObject, FName RowName)
{
	bool bResult = false;

	if (DataObject && DataObject->GetRowMap().Contains(RowName))
	{
		const FScopedTransaction Transaction(LOCTEXT("ResetDataObjectRowToDefault", "Reset Data Object Row to Default Values"));

		BroadcastPreChange(DataObject, EDataObjectChangeInfo::RowData);
		DataObject->Modify();

		uint8* RowData = DataObject->GetRowMap()[RowName];

		if (const UUserDefinedStruct* UDStruct = Cast<const UUserDefinedStruct>(DataObject->RowStruct))
		{
			UDStruct->InitializeDefaultValue(RowData);
			bResult = true;
		}

		BroadcastPostChange(DataObject, EDataObjectChangeInfo::RowData);
	}

	return bResult;
}

void FDataObjectEditorUtils::BroadcastPreChange(UEndDataObjectBase* DataObject, EDataObjectChangeInfo Info)
{
	FDataObjectEditorManager::Get().PreChange(DataObject, Info);
}

void FDataObjectEditorUtils::BroadcastPostChange(UEndDataObjectBase* DataObject, EDataObjectChangeInfo Info)
{
	if (DataObject && (EDataObjectChangeInfo::RowList == Info))
	{
		//for (TObjectIterator<UK2Node_GetDataTableRow> It(RF_Transient | RF_ClassDefaultObject, /** bIncludeDerivedClasses */ true, /** InternalExcludeFlags */ EInternalObjectFlags::PendingKill); It; ++It)
		//{
		//	It->OnDataObjectRowListChanged(DataObject);
		//}
	}
	FDataObjectEditorManager::Get().PostChange(DataObject, Info);
}

void FDataObjectEditorUtils::CacheDataObjectForEditing(const UEndDataObjectBase* DataObject, TArray<FDataObjectEditorColumnHeaderDataPtr>& OutAvailableColumns, TArray<FDataObjectEditorRowListViewDataPtr>& OutAvailableRows)
{
	if (!DataObject || !DataObject->RowStruct)
	{
		OutAvailableColumns.Empty();
		OutAvailableRows.Empty();
		return;
	}

	CacheDataForEditing(DataObject->RowStruct, DataObject->GetRowMap(), OutAvailableColumns, OutAvailableRows);
}

void FDataObjectEditorUtils::CacheDataForEditing(const UScriptStruct* RowStruct, const TMap<FName, uint8*>& RowMap, TArray<FDataObjectEditorColumnHeaderDataPtr>& OutAvailableColumns, TArray<FDataObjectEditorRowListViewDataPtr>& OutAvailableRows)
{
	TArray<FDataObjectEditorColumnHeaderDataPtr> OldColumns = OutAvailableColumns;
	TArray<FDataObjectEditorRowListViewDataPtr> OldRows = OutAvailableRows;

	// First build array of properties
	TArray<const FProperty*> StructProps;
	for (TFieldIterator<const FProperty> It(RowStruct); It; ++It)
	{
		const FProperty* Prop = *It;
		check(Prop);
		if (!Prop->HasMetaData(FName(TEXT("HideFromDataObjectEditorColumn"))))
		{
			StructProps.Add(Prop);
		}
	}

	TSharedRef<FSlateFontMeasure> FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	const FTextBlockStyle& CellTextStyle = FEditorStyle::GetWidgetStyle<FTextBlockStyle>("DataObjectEditor.CellText");
	static const float CellPadding = 10.0f;

	// Populate the column data
	OutAvailableColumns.Reset(StructProps.Num());
	for (int32 Index = 0; Index < StructProps.Num(); ++Index)
	{
		const FProperty* Prop = StructProps[Index];
		const FText PropertyDisplayName = DataTableUtils::GetPropertyDisplayName(Prop, FName::NameToDisplayString(Prop->GetName(), Prop->IsA<FBoolProperty>()));

		FDataObjectEditorColumnHeaderDataPtr CachedColumnData;

		// If at all possible, attempt to reuse previous columns if their data has not changed
		if (Index >= OldColumns.Num() || OldColumns[Index]->ColumnId != Prop->GetFName() || !OldColumns[Index]->DisplayName.EqualTo(PropertyDisplayName))
		{
			CachedColumnData = MakeShareable(new FDataObjectEditorColumnHeaderData());
			CachedColumnData->ColumnId = Prop->GetFName();
			CachedColumnData->DisplayName = PropertyDisplayName;
			CachedColumnData->Property = Prop;
		}
		else
		{
			CachedColumnData = OldColumns[Index];

			// Need to update property hard pointer in case it got reconstructed
			CachedColumnData->Property = Prop;
		}

		CachedColumnData->DesiredColumnWidth = FontMeasure->Measure(CachedColumnData->DisplayName, CellTextStyle.Font).X + CellPadding;

		OutAvailableColumns.Add(CachedColumnData);
	}

	// Populate the row data
	OutAvailableRows.Reset(RowMap.Num());
	int32 Index = 0;
	for (auto RowIt = RowMap.CreateConstIterator(); RowIt; ++RowIt, ++Index)
	{
		FText RowName = FText::FromName(RowIt->Key);
		FDataObjectEditorRowListViewDataPtr CachedRowData;

		// If at all possible, attempt to reuse previous rows if their data has not changed.
		if (Index >= OldRows.Num() || OldRows[Index]->RowId != RowIt->Key || !OldRows[Index]->DisplayName.EqualTo(RowName))
		{
			CachedRowData = MakeShareable(new FDataObjectEditorRowListViewData());
			CachedRowData->RowId = RowIt->Key;
			CachedRowData->DisplayName = RowName;
			CachedRowData->CellData.Reserve(StructProps.Num());
		}
		else
		{
			CachedRowData = OldRows[Index];
			CachedRowData->CellData.Reset(StructProps.Num());
		}

		CachedRowData->DesiredRowHeight = FontMeasure->GetMaxCharacterHeight(CellTextStyle.Font);
		CachedRowData->RowNum = Index + 1;

		// Always rebuild cell data
		{
			const uint8* RowData = RowIt.Value();
			for (int32 ColumnIndex = 0; ColumnIndex < StructProps.Num(); ++ColumnIndex)
			{
				const FProperty* Prop = StructProps[ColumnIndex];
				FDataObjectEditorColumnHeaderDataPtr CachedColumnData = OutAvailableColumns[ColumnIndex];

				const FText CellText = DataTableUtils::GetPropertyValueAsText(Prop, RowData);
				CachedRowData->CellData.Add(CellText);

				const FVector2D CellTextSize = FontMeasure->Measure(CellText, CellTextStyle.Font);

				CachedRowData->DesiredRowHeight = FMath::Max(CachedRowData->DesiredRowHeight, CellTextSize.Y);

				const float CellWidth = CellTextSize.X + CellPadding;
				CachedColumnData->DesiredColumnWidth = FMath::Max(CachedColumnData->DesiredColumnWidth, CellWidth);
			}
		}

		OutAvailableRows.Add(CachedRowData);
	}
}

TArray<UScriptStruct*> FDataObjectEditorUtils::GetPossibleStructs()
{
	TArray< UScriptStruct* > RowStructs;

	// Make combo of table rowstruct options
	for (TObjectIterator<UScriptStruct> It; It; ++It)
	{
		UScriptStruct* Struct = *It;
		if (IsValidTableStruct(Struct))
		{
			RowStructs.Add(Struct);
		}
	}

	RowStructs.Sort();

	return RowStructs;
}

void FDataObjectEditorUtils::GetPossibleStructAssetData(TArray<FAssetData>& StructAssets)
{
	StructAssets.Reset();

	// Make combo of table rowstruct options
	for (TObjectIterator<UScriptStruct> It; It; ++It)
	{
		UScriptStruct* Struct = *It;
		if (IsValidTableStruct(Struct))
		{
			StructAssets.Add(FAssetData(Struct));
		}
	}

	// Now get unloaded ones
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssetsByClass(UUserDefinedStruct::StaticClass()->GetFName(), AssetData);

	for (int32 AssetIndex = 0; AssetIndex < AssetData.Num(); ++AssetIndex)
	{
		const FAssetData& Asset = AssetData[AssetIndex];
		if (Asset.IsValid() && !Asset.IsAssetLoaded())
		{
			StructAssets.Add(Asset);
		}
	}

	StructAssets.Sort([](const FAssetData& A, const FAssetData& B) { return A.AssetName.LexicalLess(B.AssetName); });
}

bool FDataObjectEditorUtils::IsValidTableStruct(const UScriptStruct* Struct)
{
	const UScriptStruct* TableRowStruct = FTableRowBase::StaticStruct();

	// If a child of the table row struct base, but not itself
	const bool bBasedOnTableRowBase = TableRowStruct && Struct->IsChildOf(TableRowStruct) && (Struct != TableRowStruct);
	const bool bUDStruct = Struct->IsA<UUserDefinedStruct>();
	const bool bValidStruct = (Struct->GetOutermost() != GetTransientPackage());

	return (bBasedOnTableRowBase || bUDStruct) && bValidStruct;
}

void FDataObjectEditorUtils::AddSearchForReferencesContextMenu(FDetailWidgetRow& RowNameDetailWidget, FExecuteAction SearchForReferencesAction)
{
	if (SearchForReferencesAction.IsBound() && FEditorDelegates::OnOpenReferenceViewer.IsBound())
	{
		RowNameDetailWidget.AddCustomContextMenuAction(FUIAction(SearchForReferencesAction),
			NSLOCTEXT("FDataObjectRowUtils", "FDataObjectRowUtils_SearchForReferences", "Find Row References"),
			NSLOCTEXT("FDataObjectRowUtils", "FDataObjectRowUtils_SearchForReferencesTooltip", "Find assets that reference this Row"),
			FSlateIcon());
	}
}

FText FDataObjectEditorUtils::GetHandleShortDescription(const UObject* TableAsset, FName RowName)
{
	FText TableNameText = LOCTEXT("Description_None", "None");
	FText RowNameText = TableNameText;
	const int32 MaxChars = 15;
	FString More = TEXT("...");

	if (!TableAsset && RowName.IsNone())
	{
		// Just display None on it's own
		return TableNameText;
	}

	if (TableAsset)
	{
		FString TempString = TableAsset->GetName();

		// Chop off end if needed
		if (TempString.Len() > MaxChars)
		{
			TempString.LeftInline(MaxChars - More.Len());
			TempString.Append(More);
		}

		TableNameText = FText::AsCultureInvariant(TempString);
	}

	if (!RowName.IsNone())
	{
		FString TempString = RowName.ToString();

		// Show right side if too long, usually more important
		if (TempString.Len() > MaxChars)
		{
			TempString.RightInline(MaxChars - More.Len());
			TempString.InsertAt(0, More);
		}

		RowNameText = FText::AsCultureInvariant(TempString);
	}

	return FText::Format(LOCTEXT("HandlePreviewFormat", "{0}[{1}]"), TableNameText, RowNameText);
}

FText FDataObjectEditorUtils::GetRowTypeInfoTooltipText(FDataObjectEditorColumnHeaderDataPtr ColumnHeaderDataPtr)
{
	if (ColumnHeaderDataPtr.IsValid())
	{
		const FProperty* Property = ColumnHeaderDataPtr->Property;
		if (Property)
		{
			const FFieldClass* PropertyClass = Property->GetClass();
			const FStructProperty* StructProp = CastField<const FStructProperty>(Property);
			if (StructProp)
			{
				FString TypeName = FName::NameToDisplayString(Property->GetCPPType(), Property->IsA<FBoolProperty>());
				if (TypeName.Len())
				{
					// If type name starts with F and another capital letter, assume standard naming and remove F in the string shown to the user
					if (TypeName.StartsWith("F", ESearchCase::CaseSensitive) && TypeName.Len() > 1 && FChar::IsUpper(TypeName.GetCharArray()[1]))
					{
						TypeName.RemoveFromStart("F");
					}
					return FText::FromString(TypeName);
				}
			}
			if (PropertyClass)
			{
				return FText::FromString(PropertyClass->GetDescription());
			}

		}
	}

	return FText::GetEmpty();
}

FString FDataObjectEditorUtils::GetRowTypeTooltipDocExcerptName(FDataObjectEditorColumnHeaderDataPtr ColumnHeaderDataPtr)
{
	if (ColumnHeaderDataPtr.IsValid())
	{
		const FProperty* Property = ColumnHeaderDataPtr->Property;
		if (Property)
		{
			const FStructProperty* StructProp = CastField<const FStructProperty>(Property);
			if (StructProp)
			{
				if (StructProp->Struct == TBaseStructure<FSoftObjectPath>::Get())
				{
					return "SoftObject";
				}
				if (StructProp->Struct == TBaseStructure<FSoftClassPath>::Get())
				{
					return "SoftClass";
				}
				FString TypeName = FName::NameToDisplayString(Property->GetCPPType(), Property->IsA<FBoolProperty>());
				if (TypeName.Len())
				{
					// If type name starts with F and another capital letter, assume standard naming and remove F to match the doc excerpt name
					if (TypeName.StartsWith("F", ESearchCase::CaseSensitive) && TypeName.Len() > 1 && FChar::IsUpper(TypeName.GetCharArray()[1]))
					{
						TypeName.RemoveFromStart("F");
					}
					return TypeName;
				}
			}
			const FFieldClass* PropertyClass = Property->GetClass();
			if (PropertyClass)
			{
				if (PropertyClass == FStrProperty::StaticClass())
				{
					return "String";
				}
				FString PropertyClassName = PropertyClass->GetName();
				PropertyClassName.RemoveFromEnd("Property");
				return PropertyClassName;
			}
		}
	}

	return "";
}

#undef LOCTEXT_NAMESPACE
