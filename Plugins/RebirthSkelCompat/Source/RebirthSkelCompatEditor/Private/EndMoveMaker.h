// RebirthSkelCompat Move Maker (editor 1.8): make a character's attacks, abilities and limit breaks from any animation.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/SoftObjectPtr.h"
#include "EndSkeletonCompatDataObject.h"
#include "EndMoveMaker.generated.h"

class SDockTab;
class FSpawnTabArgs;
class UAnimSequence;
class UAnimSequenceBase;
class UAnimBoneCompressionSettings;

namespace RebirthSkelCompatEditor
{
/** The Move Maker's tab (Window > Rebirth Move Maker). */
extern const FName MoveMakerTabName;

TSharedRef<SDockTab> SpawnMoveMakerTab(const FSpawnTabArgs& Args);

/** Opens the Move Maker (or brings it to the front), on DataObject when one is given. */
void OpenMoveMakerTab(UEndSkeletonCompatDataObject* DataObject);

/** 1.11.1: ACL's safety fallback off for the game's ACL bone settings (Settings, or the game's when null); false when they are not in the project. */
bool TurnOffAclSafetyFallback(UAnimBoneCompressionSettings* Settings = nullptr);
void TurnOffAclSafetyFallbackOnLoad(UObject* Asset);
}

/**
 * The Move Maker's form, shown in its details panel. A move is made for one character (an animation set row of a Skeleton
 * Compatibility Data Object) under one of its animation names, from any animation: the move goes into the row's Moves
 * with Build on, and Build makes it (see Build on a move).
 */
UCLASS(Transient)
class UEndMoveMaker : public UObject
{
	GENERATED_BODY()

public:
	/** The Skeleton Compatibility Data Object the move goes in (Add New > Animation > Skeleton Compatibility Data Object). */
	UPROPERTY(EditAnywhere, Category = "Character")
	UEndSkeletonCompatDataObject* DataObject = nullptr;

	/** The character: one of the data object's animation set rows (its CharaSpec rows). Add a row there first for a new character: its Characters, Battle sources (its own motion folder first, the slot owner's last) and Character Skeleton. */
	UPROPERTY(EditAnywhere, Category = "Character", meta = (GetOptions = "GetCharacterOptions"))
	FString Character;

	/** Which of the character's animation names Slot lists. */
	UPROPERTY(EditAnywhere, Category = "Move")
	EEndMoveSlotKind Show = EEndMoveSlotKind::Attacks;

	/** The animation name to make: one the character's battle sets have (with its length now), or one of the row's moves. Picking one loads the row's move of that name, if it has one. */
	UPROPERTY(EditAnywhere, Category = "Move", meta = (GetOptions = "GetSlotOptions"))
	FString Slot;

	/** Optional: an animation name the sets do not have (wins over Slot), e.g. for a slot whose name the game asks this character for. */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Move")
	FString NewName;

	/** Optional: only in this set (e.g. Battle00). Empty: every set of the row that has the name. */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Move")
	FString Set;

	/** The animation to make the move from: any Anim Sequence, the character's own, another character's (Sephiroth's attack for Cloud) or an imported one. Another skeleton's is put on the character's skeleton when it is built. */
	UPROPERTY(EditAnywhere, Category = "Move")
	TSoftObjectPtr<UAnimSequence> Animation;

	/** How an animation of another skeleton is put on the character's. */
	UPROPERTY(EditAnywhere, Category = "Move")
	EEndMoveRetarget Retarget = EEndMoveRetarget::Proportions;

	/** (1.12) Optional: the character's own animation played under the move (its idle): the bones Animation does not move keep moving as in it, and "Keep the character's own pose" adds the motion to its pose. */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Move")
	TSoftObjectPtr<UAnimSequence> Base;

	/** (1.12) With a Base: the move is a loop as long as Base (for walk and run loops). */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Move")
	bool bBaseLoop = false;

	/** (1.12) "Keep the character's own pose" with a Base: an animation of Animation's skeleton whose first frame matches Base (that character's idle): how Animation differs from it is added to Base. Empty: Animation's first frame. */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Move")
	TSoftObjectPtr<UAnimSequence> MotionFrom;

	/** (1.12) "Leaning into the animation's root motion": the bone that leans with every bone under it. Empty: the hips (the bone under the root with the most bones under it). */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Move")
	FString LeanBone;

	/** (1.12) "Leaning into the animation's root motion": degrees it leans at a run. */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Move", meta = (ClampMin = "0", ClampMax = "60"))
	float Lean = 18.f;

	/** The animation's own sounds and effects (swings, trails) stay in the move. */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Move")
	bool bKeepSourceEffects = true;

	/** Every hit of the move, in seconds of Animation: open it (Open Animation), scrub to the strike and press Add Hit At Playhead. Empty: the hits of the move the notifies come from, lined up on its first hit in proportion. */
	UPROPERTY(EditAnywhere, Category = "Hits")
	TArray<FEndMoveHit> Hits;

	/** The move whose gameplay notifies (damage, combo and cancel windows) the new one gets. Empty: the character's own move of that name. For a move the character has no animation of, pick one of its moves that hits the way this one should, or give each hit a Damage Source ID. */
	UPROPERTY(EditAnywhere, Category = "Hits")
	TSoftObjectPtr<UAnimSequenceBase> NotifiesFrom;

	/** Add the row's Shot Effects (muzzle flash and gunshot) at every hit. */
	UPROPERTY(EditAnywhere, Category = "Hits")
	bool bShot = false;

	/** What the move is made from and where it goes. */
	UPROPERTY(VisibleAnywhere, Transient, Category = "About", meta = (MultiLine = "true"))
	FString About;

	UFUNCTION()
	TArray<FString> GetCharacterOptions() const;

	UFUNCTION()
	TArray<FString> GetSlotOptions() const;

	/** The animation set row Character names (INDEX_NONE: none). */
	int32 RowIndex() const;

	/** The animation name to make: New Name, else Slot without its length. */
	FString MoveName() const;

	/** The form as the row's move (Build on), keeping what the row's move of that name has besides. */
	FEndAnimSetMove MakeMove() const;

	/** A row's move into the form. */
	void TakeMove(const FEndAnimSetMove& Move);

	/** Fills About. */
	void Describe();
};
