// Fill out your copyright notice in the Description page of Project Settings.

#include "EndDataObject_Factory.h"

#include "Modules/ModuleManager.h"
#include "StructViewerModule.h"
#include "StructViewerFilter.h"

#include "Widgets/SWindow.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "EditorStyleSet.h"
#include "Input/Reply.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "EndDataObjectBase.h"
#include "EndDataObjectAction.h"
#include <Runtime/Engine/Classes/Engine/UserDefinedStruct.h>
#include "ClassViewerModule.h"
#include "ClassViewerFilter.h"

#define LOCTEXT_NAMESPACE "UEndDataObject_Factory"

UEndDataObject_Factory::UEndDataObject_Factory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Formats.Add(TEXT("xml;EndDataObjectAction"));
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UEndDataObjectAction::StaticClass(); //asset is not showing up in the list when using base class
}

FText UEndDataObject_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "Data Object");
}

uint32 UEndDataObject_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEX", LOCTEXT("AssetCategoryName", "SQEX"));
}

UObject * UEndDataObject_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	UEndDataObjectBase* DataObject = nullptr;
	if (Struct && ensure(SupportedClass == InClass))
	{
		ensure(0 != (RF_Public & flags));
		DataObject = NewObject<UEndDataObjectBase>(InParent, InClass, InName, flags);
		if (DataObject)
		{
			DataObject->RowStruct = const_cast<UScriptStruct*>(Struct);
		}
	}
	return DataObject;
}

bool UEndDataObject_Factory::ConfigureProperties()
{
	class FDataObjectStructFilter : public IStructViewerFilter
	{
	public:
		virtual bool IsStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const UScriptStruct* InStruct, TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override
		{
			const UScriptStruct* TableRowStruct = FEndDataTableRowBase::StaticStruct();

			// If a child of the table row struct base, but not itself
			const bool bBasedOnTableRowBase = TableRowStruct && InStruct->IsChildOf(TableRowStruct) && (InStruct != TableRowStruct);
			const bool bUDStruct = InStruct->IsA<UUserDefinedStruct>();
			const bool bValidStruct = (InStruct->GetOutermost() != GetTransientPackage());

			return (bBasedOnTableRowBase || bUDStruct) && bValidStruct;
		}

		virtual bool IsUnloadedStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const FName InStructPath, TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override
		{
			// Unloaded structs are always User Defined Structs, and User Defined Structs are always allowed
			// They will be re-validated by IsStructAllowed once loaded during the pick
			return true;
		}
	};

	class FDataTableFactoryUI : public TSharedFromThis<FDataTableFactoryUI>
	{
	public:
		FReply OnCreate()
		{
			check(ResultStruct);
			if (PickerWindow.IsValid())
			{
				PickerWindow->RequestDestroyWindow();
			}
			return FReply::Handled();
		}

		FReply OnCancel()
		{
			ResultStruct = nullptr;
			if (PickerWindow.IsValid())
			{
				PickerWindow->RequestDestroyWindow();
			}
			return FReply::Handled();
		}

		bool IsStructSelected() const
		{
			return ResultStruct != nullptr;
		}

		void OnPickedStruct(const UScriptStruct* ChosenStruct)
		{
			ResultStruct = ChosenStruct;
			StructPickerAnchor->SetIsOpen(false);
		}

		FText OnGetComboTextValue() const
		{
			return ResultStruct
				? FText::AsCultureInvariant(ResultStruct->GetName())
				: LOCTEXT("None", "None");
		}

		TSharedRef<SWidget> GenerateStructPicker()
		{
			FStructViewerModule& StructViewerModule = FModuleManager::LoadModuleChecked<FStructViewerModule>("StructViewer");

			// Fill in options
			FStructViewerInitializationOptions Options;
			Options.Mode = EStructViewerMode::StructPicker;
			Options.StructFilter = MakeShared<FDataObjectStructFilter>();

			return
				SNew(SBox)
				.WidthOverride(330)
				[
					SNew(SVerticalBox)

					+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.MaxHeight(500)
				[
					SNew(SBorder)
					.Padding(4)
				.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
				[
					StructViewerModule.CreateStructViewer(Options, FOnStructPicked::CreateSP(this, &FDataTableFactoryUI::OnPickedStruct))
				]
				]
				];
		}

		const UScriptStruct* OpenStructSelector()
		{
			FStructViewerModule& StructViewerModule = FModuleManager::LoadModuleChecked<FStructViewerModule>("StructViewer");
			ResultStruct = nullptr;

			// Fill in options
			FStructViewerInitializationOptions Options;
			Options.Mode = EStructViewerMode::StructPicker;
			Options.StructFilter = MakeShared<FDataObjectStructFilter>();

			PickerWindow = SNew(SWindow)
				.Title(LOCTEXT("DataObjectFactoryOptions", "Pick Row Structure"))
				.ClientSize(FVector2D(350, 100))
				.SupportsMinimize(false)
				.SupportsMaximize(false)
				[
					SNew(SBorder)
					.BorderImage(FEditorStyle::GetBrush("Menu.Background"))
				.Padding(10)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(StructPickerAnchor, SComboButton)
					.ContentPadding(FMargin(2, 2, 2, 1))
				.MenuPlacement(MenuPlacement_BelowAnchor)
				.ButtonContent()
				[
					SNew(STextBlock)
					.Text(this, &FDataTableFactoryUI::OnGetComboTextValue)
				]
			.OnGetMenuContent(this, &FDataTableFactoryUI::GenerateStructPicker)
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Right)
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("OK", "OK"))
				.IsEnabled(this, &FDataTableFactoryUI::IsStructSelected)
				.OnClicked(this, &FDataTableFactoryUI::OnCreate)
				]
			+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("Cancel", "Cancel"))
				.OnClicked(this, &FDataTableFactoryUI::OnCancel)
				]
				]
				]
				];

			GEditor->EditorAddModalWindow(PickerWindow.ToSharedRef());
			PickerWindow.Reset();

			return ResultStruct;
		}

	private:
		TSharedPtr<SWindow> PickerWindow;
		TSharedPtr<SComboButton> StructPickerAnchor;
		const UScriptStruct* ResultStruct = nullptr;
	};

	TSharedRef<FDataTableFactoryUI> StructSelector = MakeShareable(new FDataTableFactoryUI());
	Struct = StructSelector->OpenStructSelector();

	return Struct != nullptr;
}
bool UEndDataObject_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UEndDataObject_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	UEndDataObjectBase* ImportedAsset = NewObject<UEndDataObjectBase>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE