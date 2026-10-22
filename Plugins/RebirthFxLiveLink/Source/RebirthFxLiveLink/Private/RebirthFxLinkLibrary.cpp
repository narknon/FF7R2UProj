#include "RebirthFxLinkLibrary.h"

#include "RebirthFxLinkPaths.h"
#include "RebirthFxLinkGameAssets.h"

#include "EditorStyleSet.h"
#include "Framework/Application/SlateApplication.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SWindow.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"

namespace RebirthFxLinkLibraryDetail
{
	bool WriteFile(const TArray<uint8>& Bytes, const FString& Filename, FString& OutError)
	{
		const FString Folder = FPaths::GetPath(Filename);
		if (!Folder.IsEmpty())
		{
			IFileManager::Get().MakeDirectory(*Folder, true);
		}
		if (!FFileHelper::SaveArrayToFile(Bytes, *Filename))
		{
			OutError = TEXT("could not write ") + Filename;
			return false;
		}
		return true;
	}

	TArray<FString> Words(const FString& Filter)
	{
		TArray<FString> Out;
		Filter.TrimStartAndEnd().ParseIntoArrayWS(Out);
		return Out;
	}

	bool Matches(const FString& Item, const TArray<FString>& Words)
	{
		for (const FString& Word : Words)
		{
			if (!Item.Contains(Word, ESearchCase::IgnoreCase))
			{
				return false;
			}
		}
		return true;
	}
}

FString URebirthFxLinkLibrary::SaveGamePackageToFile(const FString& PackageName, const FString& Filename)
{
	TArray<uint8> Bytes;
	FString Error;
	if (!RebirthFxLinkGameAssets::FGameIndex::Get().ReadPackage(FName(*PackageName.TrimStartAndEnd()), Bytes, Error))
	{
		return Error.IsEmpty() ? TEXT("the package could not be read") : Error;
	}
	if (!RebirthFxLinkLibraryDetail::WriteFile(Bytes, Filename, Error))
	{
		return Error;
	}
	return FString();
}

FString URebirthFxLinkLibrary::SaveGameContainerHeaderToFile(const FString& PackageName, const FString& Filename, FString& OutContainer)
{
	OutContainer.Reset();
	TArray<uint8> Bytes;
	FString Error;
	if (!RebirthFxLinkGameAssets::FGameIndex::Get().ReadContainerHeaderFor(FName(*PackageName.TrimStartAndEnd()), Bytes, OutContainer, Error))
	{
		return Error.IsEmpty() ? TEXT("the container header could not be read") : Error;
	}
	if (!RebirthFxLinkLibraryDetail::WriteFile(Bytes, Filename, Error))
	{
		return Error;
	}
	return FString();
}

TArray<FString> URebirthFxLinkLibrary::FindGamePackagesMatching(const FString& Filter, int32 MaxResults)
{
	TArray<FString> Found;
	RebirthFxLinkGameAssets::FGameIndex& Index = RebirthFxLinkGameAssets::FGameIndex::Get();
	FString Error;
	if (!Index.Initialize(Error))
	{
		return Found;
	}
	const TArray<FString> Words = RebirthFxLinkLibraryDetail::Words(Filter);
	TArray<FName> Packages;
	Index.GetPackageNames(Packages);
	for (const FName& Package : Packages)
	{
		const FString Path = Package.ToString();
		if (RebirthFxLinkLibraryDetail::Matches(Path, Words))
		{
			Found.Add(Path);
			if (MaxResults > 0 && Found.Num() >= MaxResults)
			{
				break;
			}
		}
	}
	return Found;
}

FString URebirthFxLinkLibrary::GetGamePaksDirectory()
{
	return RebirthFxLinkPaths::FindPaksDirectory(false);
}

FString URebirthFxLinkLibrary::PickFromList(const FString& Title, const FString& Prompt, const TArray<FString>& Items, const FString& InitialFilter)
{
	if (!FSlateApplication::IsInitialized() || Items.Num() == 0)
	{
		return FString();
	}
	struct FState
	{
		TArray<TSharedPtr<FString>> All;
		TArray<TSharedPtr<FString>> Shown;
		TSharedPtr<SListView<TSharedPtr<FString>>> List;
		TSharedPtr<SWindow> Window;
		FString Chosen;

		void Refresh(const FString& Filter)
		{
			const TArray<FString> Words = RebirthFxLinkLibraryDetail::Words(Filter);
			Shown.Reset();
			for (const TSharedPtr<FString>& Item : All)
			{
				if (RebirthFxLinkLibraryDetail::Matches(*Item, Words))
				{
					Shown.Add(Item);
				}
			}
			if (List.IsValid())
			{
				List->RequestListRefresh();
			}
		}

		void Choose(TSharedPtr<FString> Item)
		{
			if (!Item.IsValid())
			{
				const TArray<TSharedPtr<FString>> Selected = List.IsValid() ? List->GetSelectedItems() : TArray<TSharedPtr<FString>>();
				Item = Selected.Num() > 0 ? Selected[0] : (Shown.Num() == 1 ? Shown[0] : nullptr);
			}
			if (Item.IsValid())
			{
				Chosen = *Item;
				if (Window.IsValid())
				{
					Window->RequestDestroyWindow();
				}
			}
		}
	};
	TSharedRef<FState> State = MakeShared<FState>();
	for (const FString& Item : Items)
	{
		State->All.Add(MakeShared<FString>(Item));
	}
	State->Refresh(InitialFilter);

	TSharedRef<SWindow> Window = SNew(SWindow)
		.Title(FText::FromString(Title.IsEmpty() ? FString(TEXT("Choose")) : Title))
		.ClientSize(FVector2D(820.f, 560.f))
		.SupportsMinimize(false)
		.SupportsMaximize(false)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
			.Padding(8.f)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 6.f)
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.Text(FText::FromString(Prompt))
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 6.f)
				[
					SNew(SSearchBox)
					.InitialText(FText::FromString(InitialFilter))
					.OnTextChanged_Lambda([State](const FText& Text) { State->Refresh(Text.ToString()); })
					.OnTextCommitted_Lambda([State](const FText& Text, ETextCommit::Type Commit)
					{
						if (Commit == ETextCommit::OnEnter)
						{
							State->Choose(nullptr);
						}
					})
				]
				+ SVerticalBox::Slot().FillHeight(1.f)
				[
					SAssignNew(State->List, SListView<TSharedPtr<FString>>)
					.ListItemsSource(&State->Shown)
					.SelectionMode(ESelectionMode::Single)
					.OnGenerateRow_Lambda([](TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& Owner) -> TSharedRef<ITableRow>
					{
						return SNew(STableRow<TSharedPtr<FString>>, Owner)
						[
							SNew(STextBlock).Text(FText::FromString(Item.IsValid() ? *Item : FString()))
						];
					})
					.OnMouseButtonDoubleClick_Lambda([State](TSharedPtr<FString> Item) { State->Choose(Item); })
				]
				+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Right).Padding(0.f, 6.f, 0.f, 0.f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 6.f, 0.f)
					[
						SNew(SButton)
						.Text(FText::FromString(TEXT("Open")))
						.OnClicked_Lambda([State]() { State->Choose(nullptr); return FReply::Handled(); })
					]
					+ SHorizontalBox::Slot().AutoWidth()
					[
						SNew(SButton)
						.Text(FText::FromString(TEXT("Cancel")))
						.OnClicked_Lambda([State]()
						{
							State->Chosen.Reset();
							if (State->Window.IsValid())
							{
								State->Window->RequestDestroyWindow();
							}
							return FReply::Handled();
						})
					]
				]
			]
		];
	State->Window = Window;
	FSlateApplication::Get().AddModalWindow(Window, FSlateApplication::Get().GetActiveTopLevelWindow());
	State->Window.Reset();
	return State->Chosen;
}
