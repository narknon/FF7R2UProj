// RebirthSkelCompat Move Maker (editor 1.8): make a character's attacks, abilities and limit breaks from any animation.
#include "EndMoveMaker.h"

#include "Animation/AnimSequence.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "Animation/DebugSkelMeshComponent.h"
#include "Animation/Skeleton.h"
#include "Editor.h"
#include "Framework/Docking/TabManager.h"
#include "IDetailsView.h"
#include "Misc/PackageName.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "UObject/Package.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/UObjectIterator.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SCompoundWidget.h"

#define LOCTEXT_NAMESPACE "RebirthMoveMaker"

// Named, not anonymous: the module may be compiled as one unity file with the data object's source.
namespace RebirthMoveMakerUtil
{
// "/Game/A/B", "AnimSequence'/Game/A/B.B'" -> "/Game/A/B.B".
FString ObjectPathOf(FString Path)
{
	Path.TrimStartAndEndInline();
	int32 Quote = INDEX_NONE;
	if (Path.FindChar(TEXT('\''), Quote))
	{
		Path = Path.Mid(Quote + 1);
		Path.RemoveFromEnd(TEXT("'"));
	}
	if (!Path.IsEmpty() && !Path.Contains(TEXT(".")))
	{
		FString Name = Path;
		int32 Slash = INDEX_NONE;
		if (Path.FindLastChar(TEXT('/'), Slash))
		{
			Name = Path.Mid(Slash + 1);
		}
		Path += TEXT(".") + Name;
	}
	return Path;
}

// Where the animation editor showing Anim has its playhead (the first one found), in seconds.
bool PlayheadOf(const UAnimSequenceBase* Anim, float& OutTime)
{
	if (!Anim)
	{
		return false;
	}
	for (TObjectIterator<UDebugSkelMeshComponent> It; It; ++It)
	{
		UDebugSkelMeshComponent* Component = *It;
		if (!Component || Component->IsPendingKill() || Component->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
		{
			continue;
		}
		const UAnimSingleNodeInstance* Instance = Cast<UAnimSingleNodeInstance>(Component->GetAnimInstance());
		if (Instance && Instance->GetAnimationAsset() == Anim)
		{
			OutTime = Instance->GetCurrentTime();
			return true;
		}
	}
	return false;
}

bool OpenInEditor(UObject* Asset)
{
	UAssetEditorSubsystem* Editors = GEditor ? GEditor->GetEditorSubsystem<UAssetEditorSubsystem>() : nullptr;
	return Asset && Editors && Editors->OpenEditorForAsset(Asset);
}
} // namespace RebirthMoveMakerUtil

// ------------------------------------------------------------------------------------------------
// The form
// ------------------------------------------------------------------------------------------------
TArray<FString> UEndMoveMaker::GetCharacterOptions() const
{
	return DataObject ? DataObject->MoveMakerRowLabels() : TArray<FString>();
}

TArray<FString> UEndMoveMaker::GetSlotOptions() const
{
	const int32 Row = RowIndex();
	return DataObject && Row != INDEX_NONE ? DataObject->MoveMakerSlots(Row, Show) : TArray<FString>();
}

int32 UEndMoveMaker::RowIndex() const
{
	if (!DataObject)
	{
		return INDEX_NONE;
	}
	FString Left;
	if (Character.TrimStartAndEnd().Split(TEXT(":"), &Left, nullptr) && Left.TrimStartAndEnd().IsNumeric())
	{
		const int32 Index = FCString::Atoi(*Left.TrimStartAndEnd());
		return DataObject->AnimationSets.IsValidIndex(Index) ? Index : INDEX_NONE;
	}
	return DataObject->AnimationSets.Num() == 1 ? 0 : INDEX_NONE;
}

FString UEndMoveMaker::MoveName() const
{
	const FString New = NewName.TrimStartAndEnd();
	if (!New.IsEmpty())
	{
		return New;
	}
	FString Name = Slot.TrimStartAndEnd();
	int32 Paren = INDEX_NONE;
	if (Name.FindChar(TEXT('('), Paren))
	{
		Name = Name.Left(Paren).TrimStartAndEnd();
	}
	return Name;
}

FEndAnimSetMove UEndMoveMaker::MakeMove() const
{
	FEndAnimSetMove Move;
	const int32 Row = RowIndex();
	const FString Name = MoveName();
	if (DataObject && Row != INDEX_NONE)
	{
		if (const FEndAnimSetMove* Old = DataObject->GetMove(Row, DataObject->FindMove(Row, Name, Set)))
		{
			Move = *Old; // keeps Then Play and Hit At
		}
	}
	Move.Name = Name;
	Move.Set = Set.TrimStartAndEnd();
	Move.Animation = Animation.IsNull() ? FString() : Animation.ToSoftObjectPath().ToString();
	Move.bBuild = true;
	Move.bShot = bShot;
	Move.Hits = Hits;
	if (Hits.Num() > 0)
	{
		Move.HitAt = 0.f;
	}
	Move.NotifiesFrom = NotifiesFrom.IsNull() ? FString() : NotifiesFrom.ToSoftObjectPath().ToString();
	Move.Retarget = Retarget;
	Move.bKeepSourceEffects = bKeepSourceEffects;
	Move.Base = Base.IsNull() ? FString() : Base.ToSoftObjectPath().ToString();
	Move.bBaseLoop = bBaseLoop;
	Move.MotionFrom = MotionFrom.IsNull() ? FString() : MotionFrom.ToSoftObjectPath().ToString();
	Move.LeanBone = LeanBone.TrimStartAndEnd();
	Move.Lean = Lean;
	return Move;
}

void UEndMoveMaker::TakeMove(const FEndAnimSetMove& Move)
{
	Set = Move.Set;
	const FString From = Move.Animation.TrimStartAndEnd();
	Animation = From.IsEmpty() ? TSoftObjectPtr<UAnimSequence>() : TSoftObjectPtr<UAnimSequence>(FSoftObjectPath(RebirthMoveMakerUtil::ObjectPathOf(From)));
	Hits = Move.Hits;
	const FString Notifies = Move.NotifiesFrom.TrimStartAndEnd();
	NotifiesFrom = Notifies.IsEmpty() ? TSoftObjectPtr<UAnimSequenceBase>() : TSoftObjectPtr<UAnimSequenceBase>(FSoftObjectPath(RebirthMoveMakerUtil::ObjectPathOf(Notifies)));
	bShot = Move.bShot;
	Retarget = Move.Retarget;
	bKeepSourceEffects = Move.bKeepSourceEffects;
	const FString Under = Move.Base.TrimStartAndEnd();
	Base = Under.IsEmpty() ? TSoftObjectPtr<UAnimSequence>() : TSoftObjectPtr<UAnimSequence>(FSoftObjectPath(RebirthMoveMakerUtil::ObjectPathOf(Under)));
	bBaseLoop = Move.bBaseLoop;
	const FString Reference = Move.MotionFrom.TrimStartAndEnd();
	MotionFrom = Reference.IsEmpty() ? TSoftObjectPtr<UAnimSequence>() : TSoftObjectPtr<UAnimSequence>(FSoftObjectPath(RebirthMoveMakerUtil::ObjectPathOf(Reference)));
	LeanBone = Move.LeanBone;
	Lean = Move.Lean;
}

void UEndMoveMaker::Describe()
{
	if (!DataObject)
	{
		About = TEXT("Pick the Skeleton Compatibility Data Object the move goes in (Data Object), then the character.");
		return;
	}
	const int32 Row = RowIndex();
	if (Row == INDEX_NONE)
	{
		About = DataObject->AnimationSets.Num() == 0
					? TEXT("The data object has no animation set row yet: add one for the character there (Characters, Battle sources with its own motion folder first and the slot owner's last, Character Skeleton).")
					: TEXT("Pick the character (one of the data object's animation set rows).");
		return;
	}
	TArray<FString> Lines;
	USkeleton* Own = DataObject->CharacterSkeletonOf(Row);
	Lines.Add(FString::Printf(TEXT("Character skeleton: %s"), Own ? *Own->GetPathName() : TEXT("not set: the move is built on the animation's own skeleton (set the row's Character Skeleton to build on the character's)")));
	if (UAnimSequence* Source = Animation.LoadSynchronous())
	{
		const USkeleton* From = Source->GetSkeleton();
		Lines.Add(FString::Printf(TEXT("Animation: %s, %.2f s, skeleton %s"), *Source->GetName(), Source->SequenceLength, From ? *From->GetName() : TEXT("none")));
		if (Own && From && Own != From)
		{
			Lines.Add(FString::Printf(TEXT("    put on %s when it is built (%s)"), *Own->GetName(),
				Retarget == EEndMoveRetarget::Proportions ? TEXT("keeping the character's build")
				: Retarget == EEndMoveRetarget::Motion ? TEXT("keeping the character's own pose, the animation's motion added")
				: Retarget == EEndMoveRetarget::Lean   ? TEXT("as its Base, leaning into the animation's root motion")
													   : TEXT("with the animation's bone lengths")));
		}
	}
	else
	{
		Lines.Add(Animation.IsNull() ? FString(TEXT("Animation: pick the animation to make the move from")) : TEXT("Animation: ") + Animation.ToSoftObjectPath().ToString() + TEXT(" does not load"));
	}
	const FString Name = MoveName();
	if (Name.IsEmpty())
	{
		Lines.Add(TEXT("Slot: pick the animation name to make"));
	}
	else
	{
		const FEndAnimSetMove Move = MakeMove();
		FString LookedFor;
		const FString Notifies = DataObject->MoveNotifySourcePath(Row, Move, LookedFor);
		Lines.Add(Notifies.IsEmpty() ? FString::Printf(TEXT("Gameplay notifies: none found (looked for %s): set Notifies From, or a Damage Source ID on each hit"), *LookedFor)
									 : TEXT("Gameplay notifies from: ") + Notifies);
		const FString Built = DataObject->BuiltMoveObjectPath(Row, Move);
		const bool bBuilt = !Built.IsEmpty() && FPackageName::DoesPackageExist(FSoftObjectPath(Built).GetLongPackageName());
		Lines.Add(FString::Printf(TEXT("Built move: %s%s"), *Built, bBuilt ? TEXT(" (built)") : TEXT(" (not built yet)")));
		Lines.Add(DataObject->FindMove(Row, Name, Set) == INDEX_NONE ? TEXT("A new move of this row: Save Move or Build adds it.")
																	   : TEXT("The row has this move: Save Move or Build updates it."));
	}
	Lines.Add(FString::Printf(TEXT("%d hit(s) set%s"), Hits.Num(), Hits.Num() == 0 ? TEXT(": the hits of the move the notifies come from, lined up on its first hit") : TEXT("")));
	About = FString::Join(Lines, TEXT("\n"));
}

// ------------------------------------------------------------------------------------------------
// The window
// ------------------------------------------------------------------------------------------------
class SEndMoveMaker : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SEndMoveMaker) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		Form.Reset(NewObject<UEndMoveMaker>(GetTransientPackage(), NAME_None, RF_Transient));
		FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
		FDetailsViewArgs Args;
		Args.bAllowSearch = false;
		Args.bHideSelectionTip = true;
		Args.NameAreaSettings = FDetailsViewArgs::HideNameArea;
		Details = PropertyEditor.CreateDetailView(Args);
		Details->SetObject(Form.Get());
		Details->OnFinishedChangingProperties().AddSP(this, &SEndMoveMaker::OnFormChanged);
		Form->Describe();
		Report = LOCTEXT("Start", "Pick the data object and the character, the animation name to make (Slot) and the animation to make it from. Open Animation, stop the playhead on each strike and press Add Hit At Playhead, then Build.");

		ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			[
				Details.ToSharedRef()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4.f)
			[
				SNew(SWrapBox)
				.UseAllottedWidth(true)
				+ SWrapBox::Slot().Padding(2.f)[MakeButton(LOCTEXT("Load", "Load Move"), LOCTEXT("LoadTip", "Fill the form from the row's move of this name (picking a Slot does it too)."), &SEndMoveMaker::OnLoad)]
				+ SWrapBox::Slot().Padding(2.f)[MakeButton(LOCTEXT("Open", "Open Animation"), LOCTEXT("OpenTip", "Open Animation in the animation editor: play it, stop the playhead on a strike, then Add Hit At Playhead."), &SEndMoveMaker::OnOpenAnimation)]
				+ SWrapBox::Slot().Padding(2.f)[MakeButton(LOCTEXT("AddHit", "Add Hit At Playhead"), LOCTEXT("AddHitTip", "Add a hit where the playhead of the open animation editor of Animation stands."), &SEndMoveMaker::OnAddHit)]
				+ SWrapBox::Slot().Padding(2.f)[MakeButton(LOCTEXT("Save", "Save Move"), LOCTEXT("SaveTip", "Put the move in the row's Moves with Build on (save the data object to keep it)."), &SEndMoveMaker::OnSave)]
				+ SWrapBox::Slot().Padding(2.f)[MakeButton(LOCTEXT("Build", "Build"), LOCTEXT("BuildTip", "Save Move, then build it (the new animation is saved; package the project to ship it, Export Json points the move at it)."), &SEndMoveMaker::OnBuild)]
				+ SWrapBox::Slot().Padding(2.f)[MakeButton(LOCTEXT("OpenBuilt", "Open Built Move"), LOCTEXT("OpenBuiltTip", "Open the built animation: the character's skeleton, the hits and their notifies."), &SEndMoveMaker::OnOpenBuilt)]
				+ SWrapBox::Slot().Padding(2.f)[MakeButton(LOCTEXT("OpenData", "Open Data Object"), LOCTEXT("OpenDataTip", "Open the data object (Validate, Export Json)."), &SEndMoveMaker::OnOpenDataObject)]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4.f)
			[
				SNew(SBox)
				.HeightOverride(200.f)
				[
					SNew(SMultiLineEditableTextBox)
					.IsReadOnly(true)
					.AutoWrapText(true)
					.Text(this, &SEndMoveMaker::GetReport)
				]
			]
		];
	}

	void SetDataObject(UEndSkeletonCompatDataObject* Object)
	{
		if (!Object || !Form.IsValid())
		{
			return;
		}
		Form->DataObject = Object;
		if (Form->RowIndex() == INDEX_NONE && Object->AnimationSets.Num() > 0)
		{
			Form->Character = Object->MoveMakerRowLabels()[0];
		}
		Form->Describe();
		Details->ForceRefresh();
	}

private:
	TStrongObjectPtr<UEndMoveMaker> Form;
	TSharedPtr<IDetailsView> Details;
	FText Report;

	TSharedRef<SWidget> MakeButton(const FText& Label, const FText& Tip, FReply (SEndMoveMaker::*Handler)())
	{
		return SNew(SButton).Text(Label).ToolTipText(Tip).OnClicked(this, Handler);
	}

	FText GetReport() const { return Report; }

	void SetReport(const FString& Text) { Report = FText::FromString(Text); }

	void Refresh()
	{
		Form->Describe();
		Details->ForceRefresh();
	}

	// The row and move name, or a message why the form is not ready.
	bool Ready(int32& OutRow, FString& OutName, bool bNeedAnimation)
	{
		OutRow = Form->RowIndex();
		OutName = Form->MoveName();
		FString Problem;
		if (!Form->DataObject)
		{
			Problem = TEXT("Pick the Skeleton Compatibility Data Object (Data Object).");
		}
		else if (OutRow == INDEX_NONE)
		{
			Problem = TEXT("Pick the character (an animation set row of the data object).");
		}
		else if (OutName.IsEmpty())
		{
			Problem = TEXT("Pick the animation name to make (Slot), or type one in New Name.");
		}
		else if (bNeedAnimation && Form->Animation.IsNull())
		{
			Problem = TEXT("Pick the animation to make the move from (Animation).");
		}
		if (!Problem.IsEmpty())
		{
			SetReport(Problem);
			return false;
		}
		return true;
	}

	bool LoadRowMove()
	{
		const int32 Row = Form->RowIndex();
		const FString Name = Form->MoveName();
		if (!Form->DataObject || Row == INDEX_NONE || Name.IsEmpty())
		{
			return false;
		}
		const FEndAnimSetMove* Move = Form->DataObject->GetMove(Row, Form->DataObject->FindMove(Row, Name, Form->Set));
		if (!Move)
		{
			return false;
		}
		Form->TakeMove(*Move);
		return true;
	}

	void OnFormChanged(const FPropertyChangedEvent& Event)
	{
		const FName Member = Event.MemberProperty ? Event.MemberProperty->GetFName() : Event.GetPropertyName();
		if (Member == GET_MEMBER_NAME_CHECKED(UEndMoveMaker, DataObject) && Form->DataObject && Form->RowIndex() == INDEX_NONE &&
			Form->DataObject->AnimationSets.Num() > 0)
		{
			Form->Character = Form->DataObject->MoveMakerRowLabels()[0];
		}
		if ((Member == GET_MEMBER_NAME_CHECKED(UEndMoveMaker, Slot) || Member == GET_MEMBER_NAME_CHECKED(UEndMoveMaker, NewName) ||
			 Member == GET_MEMBER_NAME_CHECKED(UEndMoveMaker, Character)) && LoadRowMove())
		{
			SetReport(FString::Printf(TEXT("Loaded the row's move %s."), *Form->MoveName()));
		}
		Refresh();
	}

	FReply OnLoad()
	{
		int32 Row = INDEX_NONE;
		FString Name;
		if (Ready(Row, Name, false))
		{
			SetReport(LoadRowMove() ? FString::Printf(TEXT("Loaded the row's move %s."), *Name)
									: FString::Printf(TEXT("The row has no move %s yet: fill in the form and Save Move or Build."), *Name));
			Refresh();
		}
		return FReply::Handled();
	}

	FReply OnOpenAnimation()
	{
		UAnimSequence* Source = Form->Animation.LoadSynchronous();
		SetReport(RebirthMoveMakerUtil::OpenInEditor(Source) ? FString::Printf(TEXT("Opened %s: play it, stop the playhead on a strike and press Add Hit At Playhead (once per hit)."), *Source->GetName())
									   : FString(TEXT("Pick an animation that loads (Animation) first.")));
		return FReply::Handled();
	}

	FReply OnAddHit()
	{
		UAnimSequence* Source = Form->Animation.LoadSynchronous();
		float Time = 0.f;
		if (!Source)
		{
			SetReport(TEXT("Pick the animation first (Animation), then Open Animation."));
		}
		else if (!RebirthMoveMakerUtil::PlayheadOf(Source, Time))
		{
			SetReport(FString::Printf(TEXT("%s is not open in an animation editor: press Open Animation, stop the playhead on the strike, then press this again."), *Source->GetName()));
		}
		else
		{
			FEndMoveHit Hit;
			Hit.Time = FMath::Clamp(Time, 0.f, Source->SequenceLength);
			Form->Hits.Add(Hit);
			Form->Hits.StableSort([](const FEndMoveHit& A, const FEndMoveHit& B) { return A.Time < B.Time; });
			SetReport(FString::Printf(TEXT("Hit at %.3f s added (%d hit(s)). Give it a Damage Source ID, effect or sound in Hits if it needs one."), Hit.Time, Form->Hits.Num()));
			Refresh();
		}
		return FReply::Handled();
	}

	bool SaveMove(FString& OutMessage)
	{
		int32 Row = INDEX_NONE;
		FString Name;
		if (!Ready(Row, Name, true))
		{
			OutMessage = Report.ToString();
			return false;
		}
		const bool bNew = Form->DataObject->FindMove(Row, Name, Form->Set) == INDEX_NONE;
		Form->DataObject->SetMove(Row, Form->MakeMove());
		OutMessage = FString::Printf(TEXT("%s move %s of row %d with Build on (save the data object to keep it)."), bNew ? TEXT("Added") : TEXT("Updated"), *Name, Row);
		return true;
	}

	FReply OnSave()
	{
		FString Message;
		SaveMove(Message);
		SetReport(Message);
		Refresh();
		return FReply::Handled();
	}

	FReply OnBuild()
	{
		FString Message;
		if (SaveMove(Message))
		{
			FString Built;
			const bool bOk = Form->DataObject->BuildOneMove(Form->RowIndex(), Form->MoveName(), Form->Set, Built);
			SetReport(Message + TEXT("\n") + (bOk ? TEXT("") : TEXT("Not everything went right:\n")) + Built);
		}
		else
		{
			SetReport(Message);
		}
		Refresh();
		return FReply::Handled();
	}

	FReply OnOpenBuilt()
	{
		int32 Row = INDEX_NONE;
		FString Name;
		if (Ready(Row, Name, false))
		{
			const FString Path = Form->DataObject->BuiltMoveObjectPath(Row, Form->MakeMove());
			UObject* Built = Path.IsEmpty() ? nullptr : FSoftObjectPath(Path).TryLoad();
			SetReport(RebirthMoveMakerUtil::OpenInEditor(Built) ? FString::Printf(TEXT("Opened %s."), *Path) : FString::Printf(TEXT("%s is not built yet: press Build."), *Path));
		}
		return FReply::Handled();
	}

	FReply OnOpenDataObject()
	{
		SetReport(RebirthMoveMakerUtil::OpenInEditor(Form->DataObject) ? FString(TEXT("Opened the data object.")) : FString(TEXT("Pick the data object first.")));
		return FReply::Handled();
	}
};

// ------------------------------------------------------------------------------------------------
// The tab
// ------------------------------------------------------------------------------------------------
namespace RebirthSkelCompatEditor
{
const FName MoveMakerTabName(TEXT("RebirthMoveMaker"));

namespace
{
TWeakPtr<SEndMoveMaker> CurrentMoveMaker;
TWeakObjectPtr<UEndSkeletonCompatDataObject> PendingDataObject;
}

TSharedRef<SDockTab> SpawnMoveMakerTab(const FSpawnTabArgs& Args)
{
	TSharedRef<SEndMoveMaker> Widget = SNew(SEndMoveMaker);
	CurrentMoveMaker = Widget;
	if (UEndSkeletonCompatDataObject* Pending = PendingDataObject.Get())
	{
		Widget->SetDataObject(Pending);
	}
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.Label(LOCTEXT("TabLabel", "Rebirth Move Maker"))
		[
			Widget
		];
}

void OpenMoveMakerTab(UEndSkeletonCompatDataObject* DataObject)
{
	PendingDataObject = DataObject;
	FGlobalTabmanager::Get()->TryInvokeTab(FTabId(MoveMakerTabName));
	if (TSharedPtr<SEndMoveMaker> Widget = CurrentMoveMaker.Pin())
	{
		Widget->SetDataObject(DataObject);
	}
	PendingDataObject.Reset();
}
} // namespace RebirthSkelCompatEditor

#undef LOCTEXT_NAMESPACE
