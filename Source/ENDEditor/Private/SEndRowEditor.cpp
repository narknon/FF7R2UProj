// Copyright Epic Games, Inc. All Rights Reserved.

#include "SEndRowEditor.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "EditorStyleSet.h"
#include "UObject/StructOnScope.h"
#include "Misc/MessageDialog.h"

#include "PropertyEditorModule.h"
#include "IStructureDetailsView.h"
#include "IDetailsView.h"

#define LOCTEXT_NAMESPACE "SEndRowEditor"

class FStructFromDataObject : public FStructOnScope
{
	TWeakObjectPtr<UEndDataObjectBase> DataObject;
	FName RowName;

public:
	FStructFromDataObject(UEndDataObjectBase* InDataObject, FName InRowName)
		: FStructOnScope()
		, DataObject(InDataObject)
		, RowName(InRowName)
	{}

	virtual uint8* GetStructMemory() override
	{
		return (DataObject.IsValid() && !RowName.IsNone()) ? DataObject->FindRowUnchecked(RowName) : nullptr;
	}

	virtual const uint8* GetStructMemory() const override
	{
		return (DataObject.IsValid() && !RowName.IsNone()) ? DataObject->FindRowUnchecked(RowName) : nullptr;
	}

	virtual const UScriptStruct* GetStruct() const override
	{
		return DataObject.IsValid() ? DataObject->GetRowStruct() : nullptr;
	}

	virtual UPackage* GetPackage() const override
	{
		return DataObject.IsValid() ? DataObject->GetOutermost() : nullptr;
	}

	virtual void SetPackage(UPackage* InPackage) override
	{
	}

	virtual bool IsValid() const override
	{
		return !RowName.IsNone()
			&& DataObject.IsValid()
			&& DataObject->GetRowStruct()
			&& DataObject->FindRowUnchecked(RowName);
	}

	virtual void Destroy() override
	{
		DataObject = nullptr;
		RowName = NAME_None;
	}

	FName GetRowName() const
	{
		return RowName;
	}
};

SEndRowEditor::SEndRowEditor()
	: SCompoundWidget()
{
}

SEndRowEditor::~SEndRowEditor()
{
}
void SEndRowEditor::NotifyPreChange(FProperty* PropertyAboutToChange)
{
	check(DataObject.IsValid());
	DataObject->Modify();

	FDataObjectEditorUtils::BroadcastPreChange(DataObject.Get(), FDataObjectEditorUtils::EDataObjectChangeInfo::RowData);
}

void SEndRowEditor::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged)
{
	check(DataObject.IsValid());

	FName RowName = NAME_None;
	if (SelectedName.IsValid())
	{
		RowName = *SelectedName.Get();
	}

	DataObject->HandleDataObjectChanged(RowName);
	DataObject->MarkPackageDirty();

	FDataObjectEditorUtils::BroadcastPostChange(DataObject.Get(), FDataObjectEditorUtils::EDataObjectChangeInfo::RowData);
}

/*
void SEndRowEditor::PreChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info)
{
	if (Struct && (GetScriptStruct() == Struct))
	{
		CleanBeforeChange();
	}
}

void SEndRowEditor::PostChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info)
{
	if (Struct && (GetScriptStruct() == Struct))
	{
		RefreshNameList();
		Restore();
	}
}

void SEndRowEditor::PreChange(const UEndDataObjectBase* Changed, FDataObjectEditorUtils::EDataObjectChangeInfo Info)
{
	if ((Changed == DataObject.Get()) && (FDataObjectEditorUtils::EDataObjectChangeInfo::RowList == Info))
	{
		CleanBeforeChange();
	}
}

void SEndRowEditor::PostChange(const UEndDataObjectBase* Changed, FDataObjectEditorUtils::EDataObjectChangeInfo Info)
{
	if ((Changed == DataObject.Get()) && (FDataObjectEditorUtils::EDataObjectChangeInfo::RowList == Info))
	{
		RefreshNameList();
		Restore();
	}
}*/

void SEndRowEditor::CleanBeforeChange()
{
	if (StructureDetailsView.IsValid())
	{
		StructureDetailsView->SetStructureData(NULL);
	}
	if (CurrentRow.IsValid())
	{
		CurrentRow->Destroy();
		CurrentRow.Reset();
	}
}

void SEndRowEditor::RefreshNameList()
{
	CachedRowNames.Empty();
	if (DataObject.IsValid())
	{
		auto RowNames = DataObject->GetRowNames();
		for (auto RowName : RowNames)
		{
			CachedRowNames.Add(MakeShareable(new FName(RowName)));
		}
	}
}

void SEndRowEditor::Restore()
{
	if (!SelectedName.IsValid() || !SelectedName->IsNone())
	{
		if (SelectedName.IsValid())
		{
			auto CurrentName = *SelectedName;
			SelectedName = NULL;
			for (auto Element : CachedRowNames)
			{
				if (*Element == CurrentName)
				{
					SelectedName = Element;
					break;
				}
			}
		}

		if (!SelectedName.IsValid() && CachedRowNames.Num() && CachedRowNames[0].IsValid())
		{
			SelectedName = CachedRowNames[0];
		}

		if (RowComboBox.IsValid())
		{
			RowComboBox->SetSelectedItem(SelectedName);
		}
	}
	else
	{
		if (RowComboBox.IsValid())
		{
			RowComboBox->ClearSelection();
		}
	}

	auto FinalName = SelectedName.IsValid() ? *SelectedName : NAME_None;
	CurrentRow = MakeShareable(new FStructFromDataObject(DataObject.Get(), FinalName));
	if (StructureDetailsView.IsValid())
	{
		StructureDetailsView->SetCustomName(FText::FromName(FinalName));
		StructureDetailsView->SetStructureData(CurrentRow);
	}

	RowSelectedCallback.ExecuteIfBound(FinalName);
}

UScriptStruct* SEndRowEditor::GetScriptStruct() const
{
	return DataObject.IsValid() ? DataObject->RowStruct : nullptr;
}

FName SEndRowEditor::GetCurrentName() const
{
	return SelectedName.IsValid() ? *SelectedName : NAME_None;
}

FText SEndRowEditor::GetCurrentNameAsText() const
{
	return FText::FromName(GetCurrentName());
}

FString SEndRowEditor::GetStructureDisplayName() const
{
	const auto Struct = DataObject.IsValid() ? DataObject->GetRowStruct() : nullptr;
	return Struct
		? Struct->GetDisplayNameText().ToString()
		: LOCTEXT("Error_UnknownStruct", "Error: Unknown Struct").ToString();
}

TSharedRef<SWidget> SEndRowEditor::OnGenerateWidget(TSharedPtr<FName> InItem)
{
	return SNew(STextBlock).Text(FText::FromName(InItem.IsValid() ? *InItem : NAME_None));
}

void SEndRowEditor::OnSelectionChanged(TSharedPtr<FName> InItem, ESelectInfo::Type InSeletionInfo)
{
	if (InItem.IsValid() && InItem != SelectedName)
	{
		CleanBeforeChange();

		SelectedName = InItem;

		Restore();
	}
}

void SEndRowEditor::SelectRow(FName InName)
{
	TSharedPtr<FName> NewSelectedName;
	for (auto Name : CachedRowNames)
	{
		if (Name.IsValid() && (*Name == InName))
		{
			NewSelectedName = Name;
		}
	}
	if (!NewSelectedName.IsValid())
	{
		NewSelectedName = MakeShareable(new FName(InName));
	}
	OnSelectionChanged(NewSelectedName, ESelectInfo::Direct);
}

void SEndRowEditor::HandleUndoRedo()
{
	RefreshNameList();
	Restore();
}

FReply SEndRowEditor::OnAddClicked()
{
	if (DataObject.IsValid())
	{
		FName NewName = DataTableUtils::MakeValidName(TEXT("NewRow"));
		const TArray<FName> ExisitngNames = DataObject->GetRowNames();
		while (ExisitngNames.Contains(NewName))
		{
			NewName.SetNumber(NewName.GetNumber() + 1);
		}
		FDataObjectEditorUtils::AddRow(DataObject.Get(), NewName);
		SelectRow(NewName);
	}
	return FReply::Handled();
}

FReply SEndRowEditor::OnRemoveClicked()
{
	if (DataObject.IsValid())
	{
		const FName RowToRemove = GetCurrentName();
		const int32 RowToRemoveIndex = CachedRowNames.IndexOfByPredicate([&](const TSharedPtr<FName>& InRowName) -> bool
			{
				return *InRowName == RowToRemove;
			});

		if (FDataObjectEditorUtils::RemoveRow(DataObject.Get(), RowToRemove))
		{
			// Try and keep the same row index selected
			const int32 RowIndexToSelect = FMath::Clamp(RowToRemoveIndex, 0, CachedRowNames.Num() - 1);
			if (CachedRowNames.IsValidIndex(RowIndexToSelect))
			{
				SelectRow(*CachedRowNames[RowIndexToSelect]);
			}
		}
	}
	return FReply::Handled();
}

FReply SEndRowEditor::OnMoveRowClicked(FDataObjectEditorUtils::ERowMoveDirection MoveDirection)
{
	if (DataObject.IsValid())
	{
		const FName RowToMove = GetCurrentName();
		FDataObjectEditorUtils::MoveRow(DataObject.Get(), RowToMove, MoveDirection);
	}
	return FReply::Handled();
}

FReply SEndRowEditor::OnMoveToExtentClicked(FDataObjectEditorUtils::ERowMoveDirection MoveDirection)
{
	if (DataObject.IsValid())
	{
		// We move by the row map size, as FDataObjectEditorUtils::MoveRow will automatically clamp this as appropriate
		const FName RowToMove = GetCurrentName();
		FDataObjectEditorUtils::MoveRow(DataObject.Get(), RowToMove, MoveDirection, DataObject->GetRowMap().Num());
	}
	return FReply::Handled();
}

void SEndRowEditor::OnRowRenamed(const FText& Text, ETextCommit::Type CommitType)
{
	if (!GetCurrentNameAsText().EqualTo(Text) && DataObject.IsValid())
	{
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
		for (auto Name : CachedRowNames)
		{
			if (Name.IsValid() && (*Name == NewName))
			{
				//the name already exists
				// popup an error dialog here
				const FText Message = FText::Format(LOCTEXT("DuplicateRowName", "'{0}' is already used as a row name in this table"), Text);
				FMessageDialog::Open(EAppMsgType::Ok, Message);
				return;
			}
		}

		const FName OldName = GetCurrentName();
		FDataObjectEditorUtils::RenameRow(DataObject.Get(), OldName, NewName);
		SelectRow(NewName);
	}
}

FReply SEndRowEditor::OnResetToDefaultClicked()
{
	if (DataObject.IsValid() && SelectedName.IsValid())
	{
		FDataObjectEditorUtils::ResetToDefault(DataObject.Get(), *SelectedName.Get());
	}

	return FReply::Handled();
}

EVisibility SEndRowEditor::GetResetToDefaultVisibility() const
{
	EVisibility VisibleState = EVisibility::Collapsed;

	if (DataObject.IsValid() && SelectedName.IsValid())
	{
		if (FDataObjectEditorUtils::DiffersFromDefault(DataObject.Get(), *SelectedName.Get()))
		{
			VisibleState = EVisibility::Visible;
		}
	}

	return VisibleState;
}

void SEndRowEditor::Construct(const FArguments& InArgs, UEndDataObjectBase* Changed)
{
	ConstructInternal(Changed);
}

void SEndRowEditor::ConstructInternal(UEndDataObjectBase* Changed)
{
	DataObject = Changed;
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		FDetailsViewArgs ViewArgs;
		ViewArgs.bAllowSearch = false;
		ViewArgs.bHideSelectionTip = false;
		ViewArgs.bShowActorLabel = false;
		ViewArgs.NotifyHook = this;

		FStructureDetailsViewArgs StructureViewArgs;
		StructureViewArgs.bShowObjects = false;
		StructureViewArgs.bShowAssets = true;
		StructureViewArgs.bShowClasses = true;
		StructureViewArgs.bShowInterfaces = false;

		StructureDetailsView = PropertyModule.CreateStructureDetailView(ViewArgs, StructureViewArgs, CurrentRow, LOCTEXT("RowValue", "Row Value"));
	}

	RefreshNameList();
	Restore();
	const float ButtonWidth = 85.0f;
	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2)
		[
			SNew(SBox)
			.WidthOverride(2 * ButtonWidth)
		.ToolTipText(LOCTEXT("SelectedRowTooltip", "Select a row to edit"))
		[
			SAssignNew(RowComboBox, SComboBox<TSharedPtr<FName>>)
			.OptionsSource(&CachedRowNames)
		.OnSelectionChanged(this, &SEndRowEditor::OnSelectionChanged)
		.OnGenerateWidget(this, &SEndRowEditor::OnGenerateWidget)
		.Content()
		[
			SNew(STextBlock).Text(this, &SEndRowEditor::GetCurrentNameAsText)
		]
		]
		]
	+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2)
		[
			SNew(SButton)
			.OnClicked(this, &SEndRowEditor::OnResetToDefaultClicked)
		.Visibility(this, &SEndRowEditor::GetResetToDefaultVisibility)
		.ContentPadding(FMargin(5.f, 0.f))
		.ToolTipText(LOCTEXT("ResetToDefaultToolTip", "Reset to Default"))
		.ButtonStyle(FEditorStyle::Get(), "NoBorder")
		.ForegroundColor(FSlateColor::UseForeground())
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Content()
		[
			SNew(SImage)
			.Image(FEditorStyle::GetBrush("PropertyWindow.DiffersFromDefault"))
		]
		]

		]
	+ SVerticalBox::Slot()
		[
			StructureDetailsView->GetWidget().ToSharedRef()
		]
		];
}

bool SEndRowEditor::IsMoveRowUpEnabled() const
{
	return true;
}

bool SEndRowEditor::IsMoveRowDownEnabled() const
{
	return true;
}

bool SEndRowEditor::IsAddRowEnabled() const
{
	return true;
}

bool SEndRowEditor::IsRemoveRowEnabled() const
{
	return true;
}

EVisibility SEndRowEditor::GetRenameVisibility() const
{
	return EVisibility::Visible;
}

#undef LOCTEXT_NAMESPACE
