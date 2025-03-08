// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Input/Reply.h"
#include "Widgets/Views/STableRow.h"
#include "Framework/Commands/UIAction.h"
#include "Framework/Application/MenuStack.h"
#include "Framework/Application/SlateApplication.h"
#include "DataObjectEditorUtils.h"
#include "DragAndDrop/DecoratedDragDropOp.h"

class FEndDataObjectEditor;
class SInlineEditableTextBlock;
class SDataObjectListViewRow;

class SDataObjectRowHandle : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDataObjectRowHandle)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_ARGUMENT(TSharedPtr<SDataObjectListViewRow>, ParentRow)
		SLATE_END_ARGS()

		void Construct(const FArguments& InArgs);

	FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override
	{
		return FReply::Handled().DetectDrag(SharedThis(this), EKeys::LeftMouseButton);
	};


	FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	TSharedPtr<class FDataObjectRowDragDropOp> CreateDragDropOperation(TSharedPtr<SDataObjectListViewRow> InRow);

private:
	TWeakPtr<SDataObjectListViewRow> ParentRow;
};

/**
 * A widget to represent a row in a Data Table Editor widget. This widget allows us to do things like right-click
 * and take actions on a particular row of a Data Table.
 */
class SDataObjectListViewRow : public SMultiColumnTableRow<FDataObjectEditorRowListViewDataPtr>
{
public:

	SLATE_BEGIN_ARGS(SDataObjectListViewRow)
		: _IsEditable(true)
	{
	}
	/** The owning object. This allows us access to the actual data table being edited as well as some other API functions. */
	SLATE_ARGUMENT(TSharedPtr<FEndDataObjectEditor>, DataObjectEditor)
		/** The row we're working with to allow us to get naming information. */
		SLATE_ARGUMENT(FDataObjectEditorRowListViewDataPtr, RowDataPtr)
		SLATE_ARGUMENT(bool, IsEditable)
		SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);

	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	void OnRowRenamed(const FText& Text, ETextCommit::Type CommitType);

	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;

	FText GetCurrentNameAsText() const;
	FName GetCurrentName() const;
	uint32 GetCurrentIndex() const;

	const TArray<FText>& GetCellValues() const;

	virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);

	void SetRowForRename();

	void SetIsDragDrop(bool bInIsDragDrop);

	const FDataObjectEditorRowListViewDataPtr& GetRowDataPtr() const;

private:

	void OnSearchForReferences();
	void OnInsertNewRow(ERowInsertionPos InsertPosition);

	FReply OnRowDrop(const FDragDropEvent& DragDropEvent);

	TSharedRef<SWidget> MakeCellWidget(const int32 InRowIndex, const FName& InColumnId);

	void OnRowDragEnter(const FDragDropEvent& DragDropEvent);
	void OnRowDragLeave(const FDragDropEvent& DragDropEvent);

	virtual const FSlateBrush* GetBorder() const;

	void OnMoveToExtentClicked(FDataObjectEditorUtils::ERowMoveDirection MoveDirection);

	TSharedRef<SWidget> MakeRowActionsMenu();

	TSharedPtr<SInlineEditableTextBlock> InlineEditableText;

	TSharedPtr<FName> CurrentName;

	FDataObjectEditorRowListViewDataPtr RowDataPtr;
	TWeakPtr<FEndDataObjectEditor> DataObjectEditor;

	bool IsEditable;
	bool bIsDragDropObject;
	bool bIsHoveredDragTarget;
};

class FDataObjectRowDragDropOp : public FDecoratedDragDropOp
{
public:
	DRAG_DROP_OPERATOR_TYPE(FDataObjectRowDragDropOp, FDecoratedDragDropOp)

		FDataObjectRowDragDropOp(TSharedPtr<SDataObjectListViewRow> InRow);

	void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent);

	TSharedPtr<SWidget> DecoratorWidget;

	virtual TSharedPtr<SWidget> GetDefaultDecorator() const override
	{
		return DecoratorWidget;
	}

	TWeakPtr<class SDataObjectListViewRow> Row;

};
