// Copyright Epic Games, Inc. All Rights Reserved.

#include "SDataObjectListViewRow.h"
#include "AssetData.h"
#include "EndDataObjectEditor.h"
#include "EditorStyleSet.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "Misc/MessageDialog.h"
#include "Framework/Commands/GenericCommands.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "SDataObjectListViewRowName"

void SDataObjectListViewRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)
{
	RowDataPtr = InArgs._RowDataPtr;
	CurrentName = MakeShareable(new FName(RowDataPtr->RowId));
	DataObjectEditor = InArgs._DataObjectEditor;
	IsEditable = InArgs._IsEditable;
	SMultiColumnTableRow<FDataObjectEditorRowListViewDataPtr>::Construct(
		FSuperRowType::FArguments()
		.Style(FEditorStyle::Get(), "DataObjectEditor.CellListViewRow")
		.OnDrop(this, &SDataObjectListViewRow::OnRowDrop)
		.OnDragEnter(this, &SDataObjectListViewRow::OnRowDragEnter)
		.OnDragLeave(this, &SDataObjectListViewRow::OnRowDragLeave),
		InOwnerTableView
	);

	BorderImage = TAttribute<const FSlateBrush*>(this, &SDataObjectListViewRow::GetBorder);

}

FReply SDataObjectListViewRow::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (IsEditable && MouseEvent.GetEffectingButton() == EKeys::RightMouseButton && RowDataPtr.IsValid() && FEditorDelegates::OnOpenReferenceViewer.IsBound() && DataObjectEditor.IsValid())
	{
		FDataObjectEditorUtils::SelectRow(DataObjectEditor.Pin()->GetDataObject(), RowDataPtr->RowId);

		TSharedRef<SWidget> MenuWidget = MakeRowActionsMenu();

		FWidgetPath WidgetPath = MouseEvent.GetEventPath() != nullptr ? *MouseEvent.GetEventPath() : FWidgetPath();
		FSlateApplication::Get().PushMenu(AsShared(), WidgetPath, MenuWidget, MouseEvent.GetScreenSpacePosition(), FPopupTransitionEffect::ContextMenu);
		return FReply::Handled();
	}

	return STableRow::OnMouseButtonUp(MyGeometry, MouseEvent);
}

void SDataObjectListViewRow::OnSearchForReferences()
{
	if (DataObjectEditor.IsValid() && RowDataPtr.IsValid())
	{
		if (FEndDataObjectEditor* DataObjectEditorPtr = DataObjectEditor.Pin().Get())
		{
			UEndDataObjectBase* SourceDataObject = const_cast<UEndDataObjectBase*>(DataObjectEditorPtr->GetDataObject());

			TArray<FAssetIdentifier> AssetIdentifiers;
			AssetIdentifiers.Add(FAssetIdentifier(SourceDataObject, RowDataPtr->RowId));

			FEditorDelegates::OnOpenReferenceViewer.Broadcast(AssetIdentifiers, FReferenceViewerParams());
		}
	}
}

void SDataObjectListViewRow::OnInsertNewRow(ERowInsertionPos InsertPosition)
{
	if (DataObjectEditor.IsValid() && RowDataPtr.IsValid())
	{
		if (FEndDataObjectEditor* DataObjectEditorPtr = DataObjectEditor.Pin().Get())
		{
			UEndDataObjectBase* SourceDataObject = const_cast<UEndDataObjectBase*>(DataObjectEditorPtr->GetDataObject());

			if (SourceDataObject)
			{
				FName NewName = DataTableUtils::MakeValidName(TEXT("NewRow"));
				while (SourceDataObject->GetRowMap().Contains(NewName))
				{
					NewName.SetNumber(NewName.GetNumber() + 1);
				}

				if (InsertPosition == ERowInsertionPos::Bottom)
				{
					FDataObjectEditorUtils::AddRow(SourceDataObject, NewName);
				}
				else
				{
					FDataObjectEditorUtils::AddRowAboveOrBelowSelection(SourceDataObject, *CurrentName, NewName, InsertPosition);
				}
				FDataObjectEditorUtils::SelectRow(SourceDataObject, NewName);

				//DataObjectEditorPtr->SetDefaultSort();
			}
		}
	}
}

FReply SDataObjectListViewRow::OnRowDrop(const FDragDropEvent& DragDropEvent)
{
	bIsHoveredDragTarget = false;

	TSharedPtr<FDataObjectRowDragDropOp> DataObjectDropOp = DragDropEvent.GetOperationAs< FDataObjectRowDragDropOp >();
	TSharedPtr<SDataObjectListViewRow> RowPtr = nullptr;
	if (DataObjectDropOp.IsValid() && DataObjectDropOp->Row.IsValid())
	{
		RowPtr = DataObjectDropOp->Row.Pin();
	}
	if (!RowPtr.IsValid())
	{
		return FReply::Unhandled();
	}

	int32 JumpCount = (RowPtr->RowDataPtr)->RowNum - RowDataPtr->RowNum;

	if (!JumpCount)
	{
		return FReply::Handled();
	}

	FDataObjectEditorUtils::ERowMoveDirection Direction = JumpCount > 0 ? FDataObjectEditorUtils::ERowMoveDirection::Up : FDataObjectEditorUtils::ERowMoveDirection::Down;

	if (FEndDataObjectEditor* DataObjectEditorPtr = DataObjectEditor.Pin().Get())
	{
		UEndDataObjectBase* SourceDataObject = const_cast<UEndDataObjectBase*>(DataObjectEditorPtr->GetDataObject());

		if (SourceDataObject)
		{
			FName& RowId = (RowPtr->RowDataPtr)->RowId;

			FDataObjectEditorUtils::MoveRow(SourceDataObject, RowId, Direction, FMath::Abs<int32>(JumpCount));

			FDataObjectEditorUtils::SelectRow(SourceDataObject, RowId);

			DataObjectEditorPtr->SortMode = EColumnSortMode::Ascending;
			DataObjectEditorPtr->SortByColumn = FEndDataObjectEditor::RowNumberColumnId;

			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}

FReply SDataObjectListViewRow::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FKey Key = InKeyEvent.GetKey();

	if (Key == EKeys::Escape && InlineEditableText->HasKeyboardFocus())
	{
		// Clear focus
		return FReply::Handled().SetUserFocus(SharedThis(this), EFocusCause::Cleared);
	}

	return FReply::Unhandled();
}

void SDataObjectListViewRow::OnRowRenamed(const FText& Text, ETextCommit::Type CommitType)
{
	UEndDataObjectBase* DataObject = Cast<UEndDataObjectBase>(DataObjectEditor.Pin()->GetEditingObject());

	if (!GetCurrentNameAsText().EqualTo(Text) && DataObject)
	{
		if (FEndDataObjectEditor* DataObjectEditorPtr = DataObjectEditor.Pin().Get())
		{

			const TArray<FName> RowNames = DataObject->GetRowNames();

			if (Text.IsEmptyOrWhitespace() || !FName::IsValidXName(Text.ToString(), INVALID_NAME_CHARACTERS))
			{
				// Only pop up the error dialog if the rename was caused by the user's action
				if ((CommitType == ETextCommit::OnEnter) || (CommitType == ETextCommit::OnUserMovedFocus))
				{
					// popup an error dialog here
					const FText Message = FText::Format(LOCTEXT("InvalidRowName", "'{0}' is not a valid row name"), Text);
					FMessageDialog::Open(EAppMsgType::Ok, Message);
				}
				return;
			}
			const FName NewName = DataTableUtils::MakeValidName(Text.ToString());
			if (NewName == NAME_None)
			{
				// popup an error dialog here
				const FText Message = FText::Format(LOCTEXT("InvalidRowName", "'{0}' is not a valid row name"), Text);
				FMessageDialog::Open(EAppMsgType::Ok, Message);

				return;
			}
			for (const FName& Name : RowNames)
			{
				if (Name.IsValid() && (Name == NewName))
				{
					//the name already exists
					// popup an error dialog here
					const FText Message = FText::Format(LOCTEXT("DuplicateRowName", "'{0}' is already used as a row name in this table"), Text);
					FMessageDialog::Open(EAppMsgType::Ok, Message);
					return;

				}
			}

			const FName OldName = GetCurrentName();
			FDataObjectEditorUtils::RenameRow(DataObject, OldName, NewName);
			FDataObjectEditorUtils::SelectRow(DataObject, NewName);

			//DataObjectEditorPtr->SetDefaultSort();

			*CurrentName = NewName;
		}
	}
}

TSharedRef<SWidget> SDataObjectListViewRow::GenerateWidgetForColumn(const FName& ColumnName)
{
	TSharedPtr<FEndDataObjectEditor> DataObjectEditorPtr = DataObjectEditor.Pin();
	return (DataObjectEditorPtr.IsValid())
		? MakeCellWidget(IndexInList, ColumnName)
		: SNullWidget::NullWidget;
}

TSharedRef<SWidget> SDataObjectListViewRow::MakeCellWidget(const int32 InRowIndex, const FName& InColumnId)
{
	const FName RowDragDropColumnId("RowDragDrop");

	int32 ColumnIndex = 0;

	FEndDataObjectEditor* DataObjectEdit = DataObjectEditor.Pin().Get();
	TArray<FDataObjectEditorColumnHeaderDataPtr>& AvailableColumns = DataObjectEdit->AvailableColumns;

	if (InColumnId.IsEqual(RowDragDropColumnId))
	{
		return SNew(SDataObjectRowHandle)
			.Content()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			.Padding(5.0f, 1.0f)
			[
				SNew(SImage)
				.Image(FCoreStyle::Get().GetBrush("VerticalBoxDragIndicatorShort"))
			]
			]
		.ParentRow(SharedThis(this));
	}

	const FName RowNumberColumnId("RowNumber");

	if (InColumnId.IsEqual(RowNumberColumnId))
	{
		return SNew(SBox)
			.Padding(FMargin(4, 2, 4, 2))
			[
				SNew(STextBlock)
				.TextStyle(FEditorStyle::Get(), "DataObjectEditor.CellText")
			.Text(FText::FromString(FString::FromInt(RowDataPtr->RowNum)))
			.ColorAndOpacity(DataObjectEdit, &FEndDataObjectEditor::GetRowTextColor, RowDataPtr->RowId)
			.HighlightText(DataObjectEdit, &FEndDataObjectEditor::GetFilterText)
			];
	}

	const FName RowNameColumnId("RowName");

	if (InColumnId.IsEqual(RowNameColumnId))
	{
		return SNew(SBox)
			.Padding(FMargin(4, 2, 4, 2))
			[
				SAssignNew(InlineEditableText, SInlineEditableTextBlock)
				.Text(RowDataPtr->DisplayName)
			.OnTextCommitted(this, &SDataObjectListViewRow::OnRowRenamed)
			.HighlightText(DataObjectEdit, &FEndDataObjectEditor::GetFilterText)
			.ColorAndOpacity(DataObjectEdit, &FEndDataObjectEditor::GetRowTextColor, RowDataPtr->RowId)
			.IsReadOnly(!IsEditable)
			];
	}

	for (; ColumnIndex < AvailableColumns.Num(); ++ColumnIndex)
	{
		const FDataObjectEditorColumnHeaderDataPtr& ColumnData = AvailableColumns[ColumnIndex];
		if (ColumnData->ColumnId == InColumnId)
		{
			break;
		}
	}

	// Valid column ID?
	if (AvailableColumns.IsValidIndex(ColumnIndex) && RowDataPtr->CellData.IsValidIndex(ColumnIndex))
	{
		return SNew(SBox)
			.Padding(FMargin(4, 2, 4, 2))
			[
				SNew(STextBlock)
				.TextStyle(FEditorStyle::Get(), "DataObjectEditor.CellText")
			.ColorAndOpacity(DataObjectEdit, &FEndDataObjectEditor::GetRowTextColor, RowDataPtr->RowId)
			.Text(DataObjectEdit, &FEndDataObjectEditor::GetCellText, RowDataPtr, ColumnIndex)
			.HighlightText(DataObjectEdit, &FEndDataObjectEditor::GetFilterText)
			.ToolTipText(DataObjectEdit, &FEndDataObjectEditor::GetCellToolTipText, RowDataPtr, ColumnIndex)
			];
	}

	return SNullWidget::NullWidget;
}

FName SDataObjectListViewRow::GetCurrentName() const
{
	return CurrentName.IsValid() ? *CurrentName : NAME_None;

}

uint32 SDataObjectListViewRow::GetCurrentIndex() const
{
	return RowDataPtr.IsValid() ? RowDataPtr->RowNum : -1;
}

const TArray<FText>& SDataObjectListViewRow::GetCellValues() const
{
	check(RowDataPtr)
		return RowDataPtr->CellData;
}

FReply SDataObjectListViewRow::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
{
	if (InlineEditableText->IsHovered())
	{
		InlineEditableText->EnterEditingMode();
	}

	return FReply::Handled();
}

void SDataObjectListViewRow::SetRowForRename()
{
	InlineEditableText->EnterEditingMode();
}

const FDataObjectEditorRowListViewDataPtr& SDataObjectListViewRow::GetRowDataPtr() const
{
	return RowDataPtr;
}

FText SDataObjectListViewRow::GetCurrentNameAsText() const
{
	return FText::FromName(GetCurrentName());
}

void SDataObjectRowHandle::Construct(const FArguments& InArgs)
{
	ParentRow = InArgs._ParentRow;

	ChildSlot
		[
			InArgs._Content.Widget
		];
}

FReply SDataObjectRowHandle::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		TSharedPtr<FDragDropOperation> DragDropOp = CreateDragDropOperation(ParentRow.Pin());
		if (DragDropOp.IsValid())
		{
			return FReply::Handled().BeginDragDrop(DragDropOp.ToSharedRef());
		}
	}

	return FReply::Unhandled();

}

TSharedPtr<FDataObjectRowDragDropOp> SDataObjectRowHandle::CreateDragDropOperation(TSharedPtr<SDataObjectListViewRow> InRow)
{
	TSharedPtr<FDataObjectRowDragDropOp> Operation = MakeShareable(new FDataObjectRowDragDropOp(InRow));

	return Operation;
}

void SDataObjectListViewRow::SetIsDragDrop(bool bInIsDragDrop)
{
	bIsDragDropObject = bInIsDragDrop;
}


void SDataObjectListViewRow::OnRowDragEnter(const FDragDropEvent& DragDropEvent)
{
	bIsHoveredDragTarget = true;
}

void SDataObjectListViewRow::OnRowDragLeave(const FDragDropEvent& DragDropEvent)
{
	bIsHoveredDragTarget = false;
}


const FSlateBrush* SDataObjectListViewRow::GetBorder() const
{
	if (bIsDragDropObject)
	{
		return FEditorStyle::GetBrush("DataObjectEditor.DragDropObject");
	}
	else if (bIsHoveredDragTarget)
	{
		return FEditorStyle::GetBrush("DataObjectEditor.DragDropHoveredTarget");
	}
	else
	{
		return STableRow::GetBorder();
	}
}

void SDataObjectListViewRow::OnMoveToExtentClicked(FDataObjectEditorUtils::ERowMoveDirection MoveDirection)
{
	if (DataObjectEditor.IsValid())
	{
		TSharedPtr<FEndDataObjectEditor> DataObjectEditorPtr = DataObjectEditor.Pin();
		DataObjectEditorPtr->OnMoveToExtentClicked(MoveDirection);
	}
}


TSharedRef<SWidget> SDataObjectListViewRow::MakeRowActionsMenu()
{
	FMenuBuilder MenuBuilder(true, DataObjectEditor.Pin()->GetToolkitCommands());

	MenuBuilder.AddMenuEntry(
		LOCTEXT("DataTableRowMenuActions_InsertNewRow", "Insert New Row"),
		LOCTEXT("DataTableRowMenuActions_InsertNewRowTooltip", "Insert a new row"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "DataTableEditor.Add"),
		FUIAction(FExecuteAction::CreateSP(this, &SDataObjectListViewRow::OnInsertNewRow, ERowInsertionPos::Bottom))
	);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("DataTableRowMenuActions_InsertNewRowAbove", "Insert New Row Above"),
		LOCTEXT("DataTableRowMenuActions_InsertNewRowAboveTooltip", "Insert a new Row above the current selection"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateSP(this, &SDataObjectListViewRow::OnInsertNewRow, ERowInsertionPos::Above))
	);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("DataTableRowMenuActions_InsertNewRowBelow", "Insert New Row Below"),
		LOCTEXT("DataTableRowMenuActions_InsertNewRowBelowTooltip", "Insert a new Row below the current selection"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateSP(this, &SDataObjectListViewRow::OnInsertNewRow, ERowInsertionPos::Below))
	);

	MenuBuilder.AddMenuEntry(FGenericCommands::Get().Copy);
	MenuBuilder.AddMenuEntry(FGenericCommands::Get().Paste);
	MenuBuilder.AddMenuEntry(FGenericCommands::Get().Duplicate);
	MenuBuilder.AddMenuEntry(FGenericCommands::Get().Rename);
	MenuBuilder.AddMenuEntry(FGenericCommands::Get().Delete);

	MenuBuilder.AddMenuSeparator();

	MenuBuilder.AddMenuEntry(
		LOCTEXT("DataTableRowMenuActions_MoveToTopAction", "Move Row to Top"),
		LOCTEXT("DataTableRowMenuActions_MoveToTopActionTooltip", "Move selected Row to the top"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Symbols.DoubleUpArrow"),
		FUIAction(FExecuteAction::CreateSP(this, &SDataObjectListViewRow::OnMoveToExtentClicked, FDataObjectEditorUtils::ERowMoveDirection::Up))
	);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("DataTableRowMenuActions_MoveToBottom", "Move Row To Bottom"),
		LOCTEXT("DataTableRowMenuActions_MoveToBottomTooltip", "Move selected Row to the bottom"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Symbols.DoubleDownArrow"),
		FUIAction(FExecuteAction::CreateSP(this, &SDataObjectListViewRow::OnMoveToExtentClicked, FDataObjectEditorUtils::ERowMoveDirection::Down))
	);

	MenuBuilder.AddMenuSeparator();

	MenuBuilder.AddMenuEntry(
		NSLOCTEXT("FDataTableRowUtils", "FDataTableRowUtils_SearchForReferences", "Find Row References"),
		NSLOCTEXT("FDataTableRowUtils", "FDataTableRowUtils_SearchForReferencesTooltip", "Find assets that reference this Row"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateSP(this, &SDataObjectListViewRow::OnSearchForReferences))
	);

	return MenuBuilder.MakeWidget();
}

FDataObjectRowDragDropOp::FDataObjectRowDragDropOp(TSharedPtr<SDataObjectListViewRow> InRow)
{
	Row = InRow;

	TSharedPtr<SDataObjectListViewRow> RowPtr = nullptr;
	if (Row.IsValid())
	{
		RowPtr = Row.Pin();
		RowPtr->SetIsDragDrop(true);

		DecoratorWidget = SNew(SBorder)
			.Padding(8.f)
			.BorderImage(FEditorStyle::GetBrush("Graph.ConnectorFeedback.Border"))
			.Content()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::Format(NSLOCTEXT("DataTableDragDrop", "PlaceRowHere", "Place Row {0} Here"), FText::AsNumber(InRow->GetCurrentIndex())))
			]
			];

		Construct();
	}
}

void FDataObjectRowDragDropOp::OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent)
{
	FDecoratedDragDropOp::OnDrop(bDropWasHandled, MouseEvent);

	TSharedPtr<SDataObjectListViewRow> RowPtr = nullptr;
	if (Row.IsValid())
	{
		RowPtr = Row.Pin();
		RowPtr->SetIsDragDrop(false);
	}
}

#undef LOCTEXT_NAMESPACE
