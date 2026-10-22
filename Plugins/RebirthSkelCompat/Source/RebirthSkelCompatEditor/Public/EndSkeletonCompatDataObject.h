// RebirthSkelCompat: KH3-style compatible skeletons for FINAL FANTASY VII REBIRTH mods.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/EngineTypes.h"
#include "UObject/SoftObjectPtr.h"
#include "EndSkeletonCompatDataObject.generated.h"

class USkeleton;
class USkeletalMesh;

/** How a pair makes the receiving skeleton play the animation skeletons' animations (the mod's "method"). */
UENUM(BlueprintType)
enum class EEndSkelCompatMethod : uint8
{
	/** KH3 mode: animations authored on the animation skeletons are rewritten onto the receiving skeleton while they load. The receiving character keeps its own skeleton, AnimBlueprint and physics. For a swap pak that puts one character in another's place (Sephiroth over Cloud). */
	Animations UMETA(DisplayName = "Animations (KH3 mode)"),
	/** Meshes on the receiving skeleton are bound to the animation skeleton while they load and run its AnimBlueprints. For a custom mesh or outfit shown by the animation skeleton's character (a Dresscode outfit). */
	Mesh UMETA(DisplayName = "Mesh rebind"),
	/** Every listed skeleton plays the animations of every other one, both ways (Vincent and Sephiroth play Cloud's, Cloud plays theirs). The receiving skeleton is the hub: the other members' animations move onto it and their meshes are bound to it, and each character keeps its own AnimBlueprint. Needs RebirthSkelCompat 3.0 in the game. */
	Family UMETA(DisplayName = "Family (share both ways)"),
};

/** One compatibility entry: the receiving skeleton plays the animations of the animation skeletons, by one of three methods. */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndSkeletonCompatPair
{
	GENERATED_BODY()

	/** Turn this pair off without deleting it. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeleton Compatibility")
	bool bEnabled = true;

	/** Animations (KH3 mode), the mod's default: for a swap pak that puts the receiving character in the animation skeleton's character's place. Mesh rebind: for an outfit or custom mesh shown by the animation skeleton's character. Family: the skeletons share their animations both ways. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeleton Compatibility")
	EEndSkelCompatMethod Method = EEndSkelCompatMethod::Animations;

	/** Animations: the skeleton that takes the animations over (Sephiroth's, for Sephiroth over Cloud). Mesh rebind: the skeleton your meshes use; in game they are bound to an animation skeleton while they load. Family: the hub, the skeleton the family gathers on (make it the main character's, e.g. Cloud's: its characters and animations stay as they are). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeleton Compatibility")
	TSoftObjectPtr<USkeleton> ReceivingSkeleton;

	/** More skeletons that get this pair, each as if it had its own pair with the same settings. Animations pairs for several receiving skeletons of one animation skeleton share it in game (they become a family). Family: more members. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeleton Compatibility")
	TArray<TSoftObjectPtr<USkeleton>> MoreReceivingSkeletons;

	/** Skeletons the animations are authored on (Cloud's, for Sephiroth over Cloud). Mesh rebind: in priority order, the first one loaded wins. Family: the other members (their animations and meshes move onto the hub). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeleton Compatibility")
	TArray<TSoftObjectPtr<USkeleton>> AnimationSkeletons;

	/** The pair is only on while all of these are installed: a pak file name without extension (SephirothOverCloud_P) or a mod folder name in ~mods or End\Mods. Name the swap pak that puts the receiving character in the other one's place, so taking it out gives the original character its animations back. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeleton Compatibility")
	TArray<FString> RequiresPaks;

	/** Animations: optional, adopt only animations under these folders or packages, e.g. /Game/Motion/Player/PC0000_Cloud/Neutral20. Empty = all of them. Pairs with separate folders split one animation skeleton between them. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeleton Compatibility", meta = (EditCondition = "Method == EEndSkelCompatMethod::Animations"))
	TArray<FString> AdoptPaths;

	/** Mesh rebind: optional, only these meshes are rebound. Empty = every mesh on the receiving skeleton. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeleton Compatibility", meta = (EditCondition = "Method == EEndSkelCompatMethod::Mesh"))
	TArray<TSoftObjectPtr<USkeletalMesh>> ReceivingMeshes;

	/** Mesh rebind and Family: rename the mesh bones that sit under a different parent on the skeleton they are bound to, so the game's bone-hierarchy test passes (for a family member also the bones under them, so its own AnimBlueprints still run). Renamed bones keep the mesh's own pose. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Skeleton Compatibility", meta = (EditCondition = "Method != EEndSkelCompatMethod::Animations"))
	bool bFixHierarchy = true;

	/** Mesh rebind and Family: when a mesh is rebound after it is already in use, re-initialise AnimBlueprints the game refused for it. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Skeleton Compatibility", meta = (EditCondition = "Method != EEndSkelCompatMethod::Animations"))
	bool bRepairLiveComponents = true;

	/** Mesh rebind and Family: a rebound mesh keeps the sockets of its own skeleton, so weapons and effects stay on the sockets made for its body. Needs RebirthSkelCompat 3.0 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Skeleton Compatibility", meta = (EditCondition = "Method != EEndSkelCompatMethod::Animations"))
	bool bCarrySockets = true;

	/** Every character keeps its own proportions while it plays the other skeletons' animations: arms, legs, spine and fingers keep the character's own bone lengths and the hips are scaled to its height, so a taller or broader character is not squashed into the other body. Needs RebirthSkelCompat 3.2 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeleton Compatibility")
	bool bKeepProportions = false;
	/** (editor 1.14) More bones that keep the mesh's own length with Keep Proportions, as patterns: R_Feather* is every bone starting with R_Feather, *_Phy every one ending in _Phy (a wing made smaller keeps its size). Needs Create a Character System 3.8.2 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Skeleton Compatibility", meta = (EditCondition = "bKeepProportions"))
	TArray<FString> ProportionBones;
};

/** How a source of animation sets fills a character's animation names (RebirthSkelCompat 3.2). */
UENUM(BlueprintType)
enum class EEndAnimSetAutoMatch : uint8
{
	/** Same names only: for each animation name the first source that has it wins. */
	Off UMETA(DisplayName = "Same names only"),
	/** The source's attacks fill the character's basic attacks (normal and mode attacks, counters, air attacks): the same name, else another variant of the same move, else an attack of the same kind with the closest length, each used once before any is used again. Everything else comes from the next sources. */
	BasicAttacks UMETA(DisplayName = "Auto: basic attacks"),
	/** Like Basic Attacks, and the attack abilities and limit breaks too. */
	Attacks UMETA(DisplayName = "Auto: attacks, abilities, limits"),
	/** The whole set: every name it has wins (walking, damage, ...), and the attacks it lacks are matched as above. */
	WholeSet UMETA(DisplayName = "Auto: whole set"),
};

/** One source of a character's animation sets: a motion folder (every set in it), or one set. */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndAnimSetSource
{
	GENERATED_BODY()

	/** A motion folder, e.g. /Game/Motion/Player/PC0011_Vincent: each set in it (Battle00, Neutral00, ...) fills the character's set of the same name. Or one End Anim Set, e.g. /Game/Motion/Player/PC0011_Vincent/Battle00.Battle00 (Copy Reference works). Game folders that are not in this project work too. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString Path;

	/** One set only, optional: the set it fills when its own name differs, e.g. Battle00 for a set called Battle00_Gun. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString As;

	/** Use another character's set without listing moves one by one: its attacks fill the character's attack names by kind and length (the log lists every pick; Moves still win). A motion folder without a set of the asked name (Battle01) uses its Battle00. Needs RebirthSkelCompat 3.2 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	EEndAnimSetAutoMatch AutoMatch = EEndAnimSetAutoMatch::Off;

	/** Auto Match only: use only the source's animations whose name contains one of these words (any case), e.g. Shot and Gun to keep a gunner's kicks and tonfa swings out. Empty: every animation. Needs RebirthSkelCompat 3.2 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets", meta = (EditCondition = "AutoMatch != EEndAnimSetAutoMatch::Off"))
	TArray<FString> OnlyNamesWith;
};

/** How Build Moves puts an animation of another skeleton (or one of the game's own) on the character's skeleton (editor 1.8). */
UENUM(BlueprintType)
enum class EEndMoveRetarget : uint8
{
	/** The character keeps its own build: arms, legs, spine and fingers keep its bone lengths, the hips are scaled to its height, every other bone moves the way the animation moves it from its own rest pose. */
	Proportions UMETA(DisplayName = "Keep the character's build"),
	/** Every bone as the animation has it, bone lengths included (for bodies built alike). */
	AsIs UMETA(DisplayName = "Animation's own bone lengths"),
	/** (editor 1.12) Every bone keeps the character's own pose and gets the animation's change from its skeleton's rest pose, so a body built or posed otherwise (a monster with a person's upper body, bones of other axes) moves the way the animation moves: Sephiroth's flying moves on Bizarro Sephiroth. With a Base (the character's own idle), the change from Motion From's pose (that character's idle) is added to Base's pose, and the root keeps Base's (no root motion: the game moves the character). */
	Motion UMETA(DisplayName = "Keep the character's own pose (add the animation's motion)"),
	/** (editor 1.12) Needs a Base (the character's own idle): every bone moves as in Base, and Lean Bone (with every bone under it) leans the way the animation's root moves: forward, back or to a side, Lean degrees at a run, and ahead into its turns. For a body that has nothing of the animation's (a monster moving on a person's walks and runs): Bizarro Sephiroth on Sephiroth's flying locomotion. The root keeps Base's (no root motion: the game moves the character). */
	Lean UMETA(DisplayName = "Keep the character's own pose (Base), leaning into the animation's root motion"),
};

/** What a hit's effect is attached to (editor 1.8). */
UENUM(BlueprintType)
enum class EEndMoveEffectAttach : uint8
{
	/** A socket of the character's weapon (Weapon picks which, 1 = the main weapon), e.g. VFX_Muzzle01 or C_TrailA_a. */
	Weapon,
	/** A socket or bone of the character, e.g. R_Hand_a or Body_Center01. */
	Character,
};

/** One hit of a built move: when it lands, and optionally its damage source, effect and sound (editor 1.8). */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndMoveHit
{
	GENERATED_BODY()

	/** When the hit lands, in seconds of the move's Animation (Move Maker: Add Hit At Playhead takes it from the animation editor). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hits", meta = (ClampMin = "0"))
	float Time = 0.f;

	/** How long the damage window stays open, in seconds, for damage that is a window (a notify state). 0: as long as in the move the hits are copied from. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hits", meta = (ClampMin = "0"))
	float Window = 0.f;

	/** Optional: the damage source this hit deals, an ID of the game's damage table, e.g. PC0000_00_NAttack01 (copy it from the damage notify of a move that hits the way you want). Empty: the hit's damage from Notifies From (or the character's own move of that name). A move without any of those gets a new damage notify with this ID. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hits")
	FString DamageSourceID;

	/** Optional effect at the hit, a Niagara system of the game, e.g. /Game/Effect/Character/Weapon/WE1003_01_CorneoLackey_Pistol/Particle/FX_WE1003_01_Muzzle_01 (a soft path: it does not have to be in this project). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hits")
	FString Effect;

	/** The socket (or bone) the effect plays at. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hits")
	FName EffectSocket;

	/** Whether Effect Socket is on the weapon or on the character. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hits")
	EEndMoveEffectAttach EffectOn = EEndMoveEffectAttach::Weapon;

	/** How long the effect is kept, in seconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hits", meta = (ClampMin = "0.01"))
	float EffectTime = 0.3f;

	/** Optional sound at the hit: a sound bank of the game, e.g. /Game/Sound/SE/Character/Weapon/SE_WE0000_00_Cloud_BusterSword. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hits")
	FString SoundBank;

	/** The sound in that bank (its cue name). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hits")
	FName Sound;

	/** The weapon the effect and sound belong to: 1 is the character's main weapon. A character effect ignores it; a sound plays as a weapon sound. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Hits", meta = (ClampMin = "1", ClampMax = "8"))
	int32 Weapon = 1;
};

/** One chosen animation under one animation name. */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndAnimSetMove
{
	GENERATED_BODY()

	/** The animation name the game asks for, e.g. B_Atk01_0 (look it up in the character's End Anim Set). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString Name;

	/** The animation that plays under that name, e.g. /Game/Motion/Player/PC0011_Vincent/Battle00/B_NAttack01_0 (Copy Reference works). Animations of another skeleton need a pair or family for the character's skeleton. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString Animation;

	/** Optional: only in this set (e.g. Battle00); a move with a set may also add a name that set does not have. Empty: every set of the row that has the name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString Set;

	/** Optional: more animations played right after Animation, as one move, e.g. the shoot and recover pieces after an aim piece (B_AtkShot02_0, _1, _2). The mod builds an AnimComposite of them in game. Needs RebirthSkelCompat 3.2 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TArray<FString> ThenPlay;

	/** Build this move in the editor (Build Moves, or Build in the Move Maker): a new animation made from Animation under Name in the row's Build Folder, on the row's Character Skeleton, with the gameplay notifies of the character's own animation of that name (damage, combo and cancel windows, state changes, voice, face), lined up on its hits, and the row's Shot Effects if Shot is on. Animation can be any animation: one of this project, another character's, or one of the game's (it is put on the character's skeleton, see Retarget). Attacks, abilities (B_Ability01_0) and limit breaks (B_AtkLimit01_0) are all built this way. Export Json then points the move at the built animation: cook it with your mod. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	bool bBuild = false;

	/** Build only: add the row's Shot Effects (muzzle flash and gunshot sound) at every hit. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets", meta = (EditCondition = "bBuild"))
	bool bShot = false;

	/** Build only: when the first hit lands in Animation, in seconds (the shot or strike frame). 0: in proportion to the length. Hits, when set, decide instead. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets", meta = (EditCondition = "bBuild", ClampMin = "0"))
	float HitAt = 0.f;

	/** Build only, optional: every hit of the move, in order. The damage of the move the notifies come from lands at these times (its first hit at the first time, and so on); more hits than it has repeat its last hit, fewer leave its last hits out. Each hit can also name its own damage source, effect and sound. Empty: the hits land as Hit At says. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets", meta = (EditCondition = "bBuild"))
	TArray<FEndMoveHit> Hits;

	/** Build only, optional: the animation whose gameplay notifies are copied. Empty: the character's own animation of this name, looked up in the row's folder sources from the last one (the slot owner's) up, e.g. /Game/Motion/Player/PC0000_Cloud/Battle00/B_NAttack01_0. For a new move the character has no animation of (a new ability), name one of its moves that hits the way this one should. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild"))
	FString NotifiesFrom;

	/** Build only: how an Animation of another skeleton (or one of the game's own) is put on the character's skeleton. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild"))
	EEndMoveRetarget Retarget = EEndMoveRetarget::Proportions;

	/** Build only: keep the sounds and effects of Animation itself (weapon swings, trails) when it is one of the game's or of another skeleton; its gameplay notifies (damage, windows) always come from the character's own move. (An animation of this project on the character's own skeleton keeps all its notifies.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild"))
	bool bKeepSourceEffects = true;

	/** (editor 1.12.3) Build only, with Keep Source Effects: only Animation's own sounds are kept, not its effects (a monster's effects at its own sockets and size). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild && bKeepSourceEffects"))
	bool bSourceSoundsOnly = false;

	/** Build only: the move is made of Animation from this time on (seconds into it), e.g. to leave out a monster's long wind-up. 0: from its start. Hits are times in the built move. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild", ClampMin = "0"))
	float ClipStart = 0.f;

	/** Build only: ... up to this time (seconds into Animation). 0: to its end. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild", ClampMin = "0"))
	float ClipEnd = 0.f;

	/** Build only: how fast the built move plays Animation: 1.5 plays it in two thirds of the time (a monster's slow swing as a quick attack). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild", ClampMin = "0.1", ClampMax = "10"))
	float Speed = 1.f;

	/** (editor 1.12) Build only, optional: an animation of the skeleton the move is built on, played under the move (the character's idle): the bones Animation does not move (a monster's wings, tentacles, clouds) move as in it, and with Retarget "Keep the character's own pose" the animation's motion is added to its pose. It loops under the move. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild"))
	FString Base;

	/** (editor 1.12) Build only, with a Base: the move is a loop as long as Base, Animation played in it as many times as fit (a little faster or slower), so a looping move (a walk or run loop) and Base both loop without a jump. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild"))
	bool bBaseLoop = false;

	/** (editor 1.12) Build only, with Retarget "Keep the character's own pose" and a Base: an animation of Animation's skeleton whose first frame is the pose that matches Base (that character's idle): the move adds how Animation differs from it to Base's pose, so a run adds its lean and sway to the character's idle, not its whole stance. Empty: Animation's own first frame. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild"))
	FString MotionFrom;

	/** (editor 1.12) Build only, Retarget "leaning into the animation's root motion": the character's bone that leans, with every bone under it. Empty: the bone under the root with the most bones under it (its hips); the root: every bone, about the root. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild"))
	FString LeanBone;

	/** (editor 1.12) Build only, Retarget "leaning into the animation's root motion": how far it leans at a run (6 m/s), in degrees; a walk (1 m/s) leans about a third of it, and a turn twists it ahead up to about as much. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild", ClampMin = "0", ClampMax = "60"))
	float Lean = 18.f;

	/** (editor 1.12.3) Build only, Retarget "Keep the character's own pose": which bones of Animation move which bones of the character, for bones named differently or when only part of Animation's character should move this one, e.g. the little figure on a monster: "C_SmlSpine_a=C_Spine_b, L_SmlUpperArm_a=L_UpperArm_a". "@Bone": the bone of Animation the motion is taken relative to where a mapped bone has no mapped bone above it (the figure's own base, so the monster's body moving under it is left out), e.g. "@C_SmlSpine_Spo". With a map, only the mapped bones move and Animation's curves are left out; the rest keep Base's pose (or the rest pose). Empty: every bone with the same name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild"))
	FString BoneMap;

	/** (editor 1.12.3) Build only, Retarget "Keep the character's own pose": how far Animation's skeleton is turned from the character's about the up axis, in degrees: 90 when Animation's character faces X and this one faces Y. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild", ClampMin = "-180", ClampMax = "180"))
	float SourceTurn = 0.f;

	/** (editor 1.12.3) Build only, with a Base: the character stays where Base puts it (Animation's root motion is not added; an ability played in place). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (EditCondition = "bBuild"))
	bool bKeepBaseRoot = false;
};

/** What the Move Maker lists for a character (editor 1.8). */
UENUM(BlueprintType)
enum class EEndMoveSlotKind : uint8
{
	/** Ground and air attacks, mode attacks and counters (B_NAttack01_0, B_SAttack01_0, B_AAttack01_0, B_NAttackJ01_0). */
	Attacks,
	/** Abilities and their parts (B_Ability01_0, B_AtkBurst01_0). */
	Abilities,
	/** Limit breaks (B_AtkLimit01_0). */
	LimitBreaks,
	/** Every animation name of the character's battle sets. */
	Everything,
};

/** Effects Build Moves adds at every hit of a move with Shot on: a muzzle flash and a gunshot sound. The paths are soft references to game assets: they do not have to be in this project. */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndShotEffects
{
	GENERATED_BODY()

	/** Muzzle flash, a Niagara system of the game, e.g. /Game/Effect/Character/Weapon/WE1003_01_CorneoLackey_Pistol/Particle/FX_WE1003_01_Muzzle_01 (a pistol's). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString MuzzleEffect;

	/** The socket of the weapon it plays at (Vincent's Quiksilver has VFX_Muzzle01). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FName MuzzleSocket = TEXT("VFX_Muzzle01");

	/** How long the muzzle flash is kept, in seconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets", meta = (ClampMin = "0.01"))
	float MuzzleTime = 0.15f;

	/** Gunshot, a sound bank of the game, e.g. /Game/Sound/SE/Character/Weapon/SE_WE1003_01_CorneoLackey_Pistol. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString SoundBank;

	/** The sound in that bank, e.g. FX_WE1003_01_Muzzle_01 (the pistol's shot). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FName Sound;

	/** The weapon both play at: 1 is the character's main weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (ClampMin = "1", ClampMax = "8"))
	int32 Weapon = 1;
};

/** One socket stand-in: the socket the game asks for, and the socket or bone of this character that takes its place (RebirthSkelCompat 3.2). */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndSocketStandIn
{
	GENERATED_BODY()

	/** The socket the game attaches to, e.g. Attach_Weapon01 (the field holster on Cloud's back, which other bodies lack). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString Socket;

	/** The socket (or bone) of this character that takes its place, e.g. Attach_Weapon_Right01 (the right hand) or Attach_Weapon_Right02 (a hip holster). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString Use;

	/** (editor 1.14) The stand-in moved on its bone (cm): what the game attaches there sits that much further along (a sword held a little lower). Needs Create a Character System 3.8.1 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets")
	FVector Location = FVector::ZeroVector;

	/** (editor 1.14) The stand-in turned on its bone (degrees, as the socket editor shows a socket's): a weapon held at another angle. Needs Create a Character System 3.8.1 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets")
	FRotator Rotation = FRotator::ZeroRotator;

	/** (editor 1.14) What the game attaches there is scaled by this (1: as it is). Needs Create a Character System 3.8.1 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (ClampMin = "0", ClampMax = "100"))
	FVector Scale = FVector(1.f, 1.f, 1.f);

	/** (editor 1.14) What the game attaches there is shrunk out of sight (a weapon the character does not show). Needs Create a Character System 3.8.1 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets")
	bool bHidden = false;
};

/** One limit break's animation: one animation, or several played one after another as one (RebirthSkelCompat 3.2). */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndLimitBreak
{
	GENERATED_BODY()

	/** The animation played as this limit break: the first entry is B_AtkLimit01_0, the second B_AtkLimit02_0, and so on. Empty: the character keeps its own (or what Auto Match picks). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString Animation;

	/** Optional: more animations played right after it, as one limit break. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TArray<FString> ThenPlay;
};

/** One of the character's weapons' abilities in another pack (RebirthSkelCompat 3.4). */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndWeaponAbility
{
	GENERATED_BODY()

	/** The ability a weapon gives (its Equipment row's BurstAbilityID), e.g. PC0000_AtkBurst02 (Focused Thrust, Cloud's Buster Sword). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString Weapon;

	/** The BattleAbility row that weapon gives while this pack plays, e.g. PC0010_T_Blizzaga. Whether it shows (learned, or the weapon equipped) is still the game's check of the weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString Ability;
};

/**
 * The battle commands a character has while it plays one animation pack (RebirthSkelCompat 3.3): when a Lua mod or a
 * Blueprint switches the character's pack in battle (EndBattleAPI SetPrimaryAnimPack, e.g. to Battle02 for a second
 * moveset), the game mod gives its BattlePlayerParameter row these ATB abilities and limit breaks, and (3.4) its weapons
 * these abilities.
 */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndPackAbilities
{
	GENERATED_BODY()

	/** The animation pack, e.g. Battle02. Battle00 is the character's own pack: its lists also apply at every map load and after ResetPrimaryAnimPack, and packs without their own lists use them. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString Pack;

	/** This pack has its own command list (off: Battle00's, else the table's). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	bool bSetCommands = true;

	/** The ATB abilities in the command menu, in menu order: rows of the BattleAbility table, e.g. PC0010_AtkBurst01. At most 5 (the game lists the first 5 of a player row, then the character's weapon and materia abilities). Empty with Set Commands on: no abilities. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets", meta = (EditCondition = "bSetCommands"))
	TArray<FString> Commands;

	/** This pack has its own limit breaks (off: Battle00's, else the table's). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	bool bSetLimits = false;

	/** The limit breaks, limit 1 first: rows of the BattleAbility table, e.g. PC0010_Limit001. At most 3 (the game's limit flags cover 3). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets", meta = (EditCondition = "bSetLimits"))
	TArray<FString> Limits;

	/** This pack switches the abilities the character's weapons give (off: Battle00's, else the weapons' own). Needs RebirthSkelCompat 3.4 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	bool bSetWeaponAbilities = false;

	/** The abilities the character's weapons give while this pack plays: weapon's ability -> BattleAbility row. Empty with Set Weapon Abilities on: the weapons' own. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets", meta = (EditCondition = "bSetWeaponAbilities"))
	TArray<FEndWeaponAbility> WeaponAbilities;
};

/** An effect played on the character in a form (Create a Character System 3.6): a Niagara system or a Cascade particle system attached to its mesh. */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndFormEffect
{
	GENERATED_BODY()

	/** The effect: a Niagara System or a Particle System, e.g. /Game/Effect/Character/Player/PC0010_10_Sephiroth_Transform/Particle/FX_PC0010_10_Tenshi_Charge_01. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Effect;

	/** The socket or bone of the character's mesh it plays at, e.g. Spine3. Empty: the mesh's root. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Socket;

	/** Its size (1: as made). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (ClampMin = "0.01", ClampMax = "100"))
	float Scale = 1.f;

	/** How long it plays before it stops and fades. 0: the forms' Effect Seconds. (Keep Effects play for as long as the form lasts.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (ClampMin = "0", ClampMax = "60"))
	float Seconds = 0.f;
};

/** A sound played as the character switches to a form (Create a Character System 3.6): a cue of a sound bank (SQEX SEAD). */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndFormSound
{
	GENERATED_BODY()

	/** The sound bank, e.g. /Game/Sound/SE/Character/Player/SE_PC0010_00_Sephiroth_Standard. A voice bank's path with {language} where the language goes (/Game/Sound/Voice/{language}/Character/Player/VO_PC0010_00_Sephiroth) plays the bank of the language the game loaded. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Bank;

	/** The cue in that bank, e.g. SE_PC0010_10_B_AtkTenshi01_0_whoosh (or Atk_Ability_02 in the voice bank). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Cue;
};

/** A model part added in a form (Create a Character System 3.6): another skeletal mesh attached to the character's mesh (a monster's wings, face and core). */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndFormMesh
{
	GENERATED_BODY()

	/** The skeletal mesh added, e.g. /Game/Character/Enemy/EB2210_10_BizarroSephiroth_WingR/Model/EB2210_10. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Mesh;

	/** The socket or bone of the character's mesh it is attached at. Empty: the mesh's root. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Socket;

	/** It plays the character's mesh's pose (both on one skeleton: the parts of one model). Off: it keeps its own pose. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	bool bFollowPose = true;
};

/** Effects played while the character runs some abilities in a form, stopped when the ability ends (Create a Character System 3.6): a monster's conjured sword in its sword attacks. */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndFormAbilityEffects
{
	GENERATED_BODY()

	/** The abilities: BattleAbility rows, e.g. PC0010_BZ_Octaslash. A name ending in * stands for every row that starts with it: PC0010_NAtk_* is every normal attack of PC0010. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TArray<FString> Abilities;

	/** The effects played on the character while one of them runs, e.g. /Game/Effect/Character/Enemy/EB2210_BizarroSephiroth/Particle/FX_EB2210_OmniSlash_Sword_01 at socket Attack_Sword. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TArray<FEndFormEffect> Effects;
};

/**
 * One form of a character (Create a Character System 3.6): an animation pack it plays in battle (its moves, switched with
 * EndBattleAPI SetPrimaryAnimPack) and what changes with it: parts of the model shown or hidden, another model, effects
 * and sounds as it switches, effects kept while it lasts, real flying.
 */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndCharacterForm
{
	GENERATED_BODY()

	/** The form's name on the forms menu, e.g. WINGED (at most 40 letters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Name;

	/** The animation pack the form plays, e.g. Battle02: the sets the row's Battle sources and Moves give that name, and its Abilities entry (the commands and limits of the form). A pack nothing fills starts from the character's Battle00 and Battle00_Comp. Empty or Battle00: the character's own. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Pack;

	/** The parts (material slots of the character's model, listed in the forms' Parts) shown in this form; the forms' other parts are hidden. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TArray<FString> ShowParts;

	/** Another model worn in this form: a Skeletal Mesh, e.g. a monster's body /Game/Character/Enemy/EB2210_00_BizarroSephiroth_Standard/Model/EB2210_00_Body. Its pack's animations must be made for its skeleton (Build Moves builds the moves of this form's pack on it). Empty: the character's own. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Model;

	/** The AnimBlueprint the model runs in this form, e.g. the model's own (an AnimBlueprint asset or its _C class). Needed for a model on another skeleton. Empty: the character's. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString AnimBlueprint;

	/** The model's size in this form, against the character's (0.25: a quarter). 0: unchanged. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (ClampMin = "0", ClampMax = "50"))
	float Scale = 0.f;

	/** (editor 1.12.1) Build Moves: the model turned this many degrees about its up axis in this form's moves, so a model made facing another way faces the game's (the game's models face +X; an imported model facing +Y needs -90). With Model Lift, the moves also hold its root where its reference pose has it, as the game does, and place every bone under it as the animation shows it. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (ClampMin = "-180", ClampMax = "180"))
	float ModelTurn = 0.f;

	/** (editor 1.12.1) Build Moves: the model moved up (- down) in this form's moves, in its own units before Scale (cm): a model made floating high brought down to the ground. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (ClampMin = "-100000", ClampMax = "100000"))
	float ModelLift = 0.f;

	/** Model parts added in this form: other skeletal meshes attached to the character's mesh (a monster's wings, face and core). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TArray<FEndFormMesh> Meshes;

	/** The character's weapons are hidden in this form (a model that fights with its own body). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	bool bHideWeapon = false;

	/** Effects played on the character as it switches to this form: the transformation (a flash, a burst of feathers). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TArray<FEndFormEffect> Effects;

	/** Effects kept for as long as it is in this form (an aura, a glow). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TArray<FEndFormEffect> KeepEffects;

	/** Sounds played as it switches to this form. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TArray<FEndFormSound> Sounds;

	/** Real flying: the character flies while it is in this form, hovering above where the form started. Fly Up and Fly Down raise and lower it. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	bool bFly = false;

	/** How high above the ground where the form started it hovers (cm). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (EditCondition = "bFly", ClampMin = "0", ClampMax = "5000"))
	float FlyHeight = 250.f;

	/** How fast Fly Up and Fly Down raise and lower it (cm/s). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (EditCondition = "bFly", ClampMin = "0", ClampMax = "5000"))
	float FlySpeed = 600.f;

	/** The highest it goes above where the form started (cm). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (EditCondition = "bFly", ClampMin = "0", ClampMax = "20000"))
	float FlyMax = 3000.f;

	/** The input key that raises it, e.g. Gamepad_DPad_Up. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (EditCondition = "bFly"))
	FString FlyUp = TEXT("Gamepad_DPad_Up");

	/** The input key that lowers it, e.g. Gamepad_DPad_Down. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (EditCondition = "bFly"))
	FString FlyDown = TEXT("Gamepad_DPad_Down");

	/** The character switches to this form by itself when this ability ends: a BattleAbility row, e.g. PC0000_Limit002 (a limit break that transforms it). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString After;

	/** Effects played while the character runs some abilities in this form (until each ability ends), e.g. a conjured sword in the form's sword attacks. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TArray<FEndFormAbilityEffects> AbilityEffects;

	/** Super armor: hits do not make the character flinch, stagger or get knocked about in this form (they still hurt). It ends with the form, and when the character is knocked out. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	bool bSuperArmor = false;

	/** The form lasts this long, then the character turns back into Revert To by itself (once the ability it is in ends). Game time: pauses and the command menu's slow time stretch it. The time left is on screen in battle and on the forms menu. 0: for as long as you like. The normal form (the first) has no time limit. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (ClampMin = "0", ClampMax = "3600"))
	float Seconds = 0.f;

	/** Once the character leaves this form (its time up, or switched away), the form can be chosen again only this much later (the menu shows when). 0: at once. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (ClampMin = "0", ClampMax = "3600"))
	float Cooldown = 0.f;

	/** The form it turns back into when its time is up or it is knocked out: another form's name. Empty: the normal form. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString RevertTo;

	/** (editor 1.14) The form's Model goes on the game's way (its look change, the way the Toad status puts the frog on) with the character's own AnimBlueprint and weapons: for another model of the same body (another outfit, an older or a younger self). Needs Create a Character System 3.7.8 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	bool bAsLook = false;

	/** (editor 1.14) The weapon the character fights with in this form: a weapon blueprint, e.g. /Game/BluePrint/Character/Weapon/WE1021_00_SephirothIllusion_Masamune (its class). It takes its own weapon's slot while the form lasts. Empty: its own. Needs Create a Character System 3.8.2 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Weapon;

	/** (editor 1.14) Sets: while the character is in this form, the game's lookups of a set named on the left get its set named on the right, e.g. Battle00 -> Battle07, Facial00 -> Facial07 (a beast form keeps its own walks and face whatever mode the game plays). At most 8. Needs Create a Character System 3.7.5 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TMap<FString, FString> Sets;

	/** (editor 1.14) Voice: the voice bank the voice lines of the character's animations play from in this form, e.g. /Game/Sound/Voice/{language}/Character/Player/VO_PC0010_13_YoungSephiroth (one made with Sound Banks). own: the banks the animations name (the original voice). Empty: the row's Voice. Needs Create a Character System 3.9.0 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Voice;

	/** (editor 1.14) The voice banks Voice plays in place of, e.g. /Game/Sound/Voice/{language}/Character/Player/VO_PC0010_00_Sephiroth. Empty: the character voice banks of the character's CharaSpec pack. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Forms")
	TArray<FString> VoiceReplaces;

	/** (editor 1.14) The battle camera in this form, as the mod's JSON has it: a distance (600) or {"distance": 600, "height": 150, "fov": 0, "blend": 0.6}. Empty: the game's. Needs Create a Character System 3.6.16 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Forms", meta = (MultiLine = "true"))
	FString CameraJson;

	/** (editor 1.14) Cameras while some abilities run in this form, as the mod's JSON has them: [{"abilities": ["M_SMN_*"], "distance": 1500, "height": 400}]. Needs Create a Character System 3.6.16 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Forms", meta = (MultiLine = "true"))
	FString AbilityCamerasJson;

	/** (editor 1.14) The entrance played as the character switches to this form, as the mod's JSON has it (a flash, an animation, a cinematic camera, shots of a cutscene with their effects and sounds). Needs Create a Character System 3.6.6 in the game (shots: 3.6.7). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Forms", meta = (MultiLine = "true"))
	FString EntranceJson;

	/** (editor 1.14) The shooter in this form, as the mod's JSON has it: false (it does not fight as a shooter in this form), true, or {...} settings over the row's. Needs Create a Character System 3.7 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Forms", meta = (MultiLine = "true"))
	FString ShooterJson;
};

/**
 * The forms of a character and its forms menu (Create a Character System 3.6). In battle, holding Button opens a command
 * window in the game's menu art that lists the forms (7 at a time, up to 13: the list scrolls); up and down pick one and
 * letting go of the button switches to it. A switch made by anything else (a Lua mod, the game) changes the form too, and
 * the character is back in its normal form (the first) when the battle ends.
 */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndCharacterForms
{
	GENERATED_BODY()

	/** The forms, the normal one first (it plays the character's own pack, Battle00). Two to 13. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TArray<FEndCharacterForm> List;

	/** The button held to open the forms menu (an input key name): Gamepad_FaceButton_Top is Triangle. A tap stays the game's. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Button = TEXT("Gamepad_FaceButton_Top");

	/** A keyboard key that opens the menu too, e.g. T. Empty: none. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Key;

	/** How long the button is held before the menu opens (seconds; a shorter press stays the game's). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (ClampMin = "0.1", ClampMax = "5"))
	float HoldSeconds = 0.35f;

	/** The menu's heading. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	FString Title = TEXT("FORMS");

	/** Material slots of the character's model that the forms show or hide, e.g. Wing (each form's Show Parts says which it shows). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TArray<FString> Parts;

	/** Parts fade in and out this long (seconds; 0: at once). Their materials need Fade Parameter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Forms", meta = (ClampMin = "0", ClampMax = "60"))
	float FadeSeconds = 0.f;

	/** The scalar parameter of the parts' materials that fades them (1: shown). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Forms")
	FString FadeParameter = TEXT("NativePrimitiveCoverage");

	/** Effects played as parts come out (feathers as a wing opens). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TArray<FEndFormEffect> ShowEffects;

	/** Effects played as parts go. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms")
	TArray<FEndFormEffect> HideEffects;

	/** How long switch effects play (seconds); an effect can set its own. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forms", meta = (ClampMin = "0", ClampMax = "60"))
	float EffectSeconds = 2.5f;

	/** Other copies of the character's model (cutscenes, the menus' 3D views) keep the parts hidden. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Forms")
	bool bHideOnOthers = true;

	/** A timed form's time left is on screen in battle (at Timer At). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Forms")
	bool bShowTimer = true;

	/** Where the time left shows, in fractions of the screen (0.97, 0.55: by the right edge, a little below the middle). Right of the middle its right edge is there, left of it its left edge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Forms", meta = (EditCondition = "bShowTimer", ClampMin = "0", ClampMax = "1"))
	FVector2D TimerAt = FVector2D(0.97f, 0.55f);
};

/** Which animations one character plays in battle, in the field, for field actions and in cutscenes (RebirthSkelCompat 3.1). */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndAnimSetRow
{
	GENERATED_BODY()

	/** Turn this row off without deleting it. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	bool bEnabled = true;

	/** CharaSpec rows whose character this is, e.g. PC0000_00_Cloud_Standard for a character in Cloud's slot. The game asks that character for the animation names of the slot's owner. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TArray<FString> Characters;

	/** Battle: where the Battle* sets come from, in order of preference. For each animation name the first source that has it wins, so list the character's own folder first and the slot owner's last, e.g. /Game/Motion/Player/PC0011_Vincent then /Game/Motion/Player/PC0000_Cloud. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TArray<FEndAnimSetSource> Battle;

	/** Battle moves: one chosen animation under one name, for moves whose names differ between characters, e.g. a gun animation of Biggs or Rufus played as Cloud's B_Atk01_0. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TArray<FEndAnimSetMove> Moves;

	/** Field: where every other set comes from (Neutral*, Emotion*, Facial*: walking, running, swimming, emotes, faces), in the same order rule. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TArray<FEndAnimSetSource> Field;

	/** Field actions (ladders, crawl spaces, ledges): the motion folder name whose field actions the character uses, e.g. PC0000_Cloud. The game picks them by the CharaSpec row's AnimationSetParentFolder; Apply To CharaSpec writes it there. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString FieldActions;

	/** Cutscenes: the skeleton whose cutscene animations the character's mesh plays, e.g. Cloud's for a character in Cloud's slot. With Character Skeleton this makes a family with this skeleton as hub. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TSoftObjectPtr<USkeleton> Cutscene;

	/** The character's own skeleton (Vincent's), for the cutscene family, socket stand-ins and proportions. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TSoftObjectPtr<USkeleton> CharacterSkeleton;

	/** Socket stand-ins on the character's meshes: each is the socket the game asks for and the socket (or bone) of this character that takes its place, e.g. Attach_Weapon01 (the field holster on Cloud's back, which other bodies lack) -> Attach_Weapon_Right01 (the right hand) or Attach_Weapon_Right02 (a hip holster). Needs Character Skeleton and RebirthSkelCompat 3.2 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TArray<FEndSocketStandIn> Sockets;

	/** Limit breaks, in order: the first entry plays as limit 1 (B_AtkLimit01_0), the second as limit 2, ... One animation each, or several played one after another. They win over Auto Match; Moves of the same name win over them. Needs RebirthSkelCompat 3.2 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TArray<FEndLimitBreak> LimitBreaks;

	/** Keep the character's proportions: every pair and family of Character Skeleton keeps each body's own bone lengths (see a pair's Keep Proportions). Needs RebirthSkelCompat 3.2 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	bool bKeepProportions = false;

	/** Put this row before the character's rows in other compat files: its sources, moves, field actions and sockets win (a test file over a mod's own row). Needs RebirthSkelCompat 3.2 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets")
	bool bOverride = false;

	/** The character's BattlePlayerParameter row, for Abilities: pt_Cloud for a character in Cloud's slot (pt_Barret, pt_Tifa, ...). Needs RebirthSkelCompat 3.3 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString PlayerParameter;

	/** ATB abilities and limit breaks per animation pack: switching the character's pack in battle (SetPrimaryAnimPack, e.g. from a Lua mod) switches its command menu and limits too. The abilities' animations must be in that pack's sets (Battle sources or Moves). Needs Player Parameter and RebirthSkelCompat 3.3 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TArray<FEndPackAbilities> Abilities;

	/** After a pack switch, have the game recalculate the character's status (its level is set to the level it has), which is when the game builds a character's command and limit lists, so the new lists show right away. Off: they show when the game next recalculates (a new area, a level up). Needs RebirthSkelCompat 3.3 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets")
	bool bRefreshAbilities = true;

	/** Objects the game mod loads at the first map load and keeps, e.g. the CharaSpec pack of a prop that one of the abilities' damage sources spawns (/Game/DataAsset/Game/CharaSpec/CharaSpec_FA0260_01_SephirothMeteor_Battle). Needs RebirthSkelCompat 3.3 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets")
	TArray<FString> Preload;

	/** Objects the game mod puts into the characters' CharaSpec packs, next to what each pack already lists: another character's effect pack (/Game/Effect/Character/Player/PC0010_10_Sephiroth_Transform/Build/PC0010_10_Sephiroth_Transform_Effect__Pack), a sound bank. The game looks up the effects an ability's damage sources name in the effect packs of the attacker's pack, so abilities taken from another character need that character's effect pack here. Loaded at the first map load. Needs RebirthSkelCompat 3.3.1 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets")
	TArray<FString> PackAssets;

	/** Forms: what the character changes into in battle with the forms menu (hold Triangle, pick one, let go). Each form plays an animation pack (its moves and Abilities) and can show or hide parts of the model, wear another model, hide the weapons, play effects and sounds, keep an aura and fly. Needs Create a Character System 3.6 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FEndCharacterForms Forms;

	/** Where Build Moves puts the built animations: each goes to <Build Folder>/<Set>/<Name>, e.g. /Game/Motion/Player/PC0011_00_Vincent/Built/Battle00/B_NAttack01_0. Empty: /Game/RebirthSkelCompat/Built/<character>. The folder gets a Primary Asset Label for Build Chunk, so packaging puts them in that chunk. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString BuildFolder;

	/** Muzzle flash and gunshot that Build Moves adds to the moves with Shot on. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FEndShotEffects ShotEffects;

	/** Set names to look for in the folders besides the usual ones (Battle00-02, Battle00_Comp, Battle01_Comp, Neutral00/01/10/20, Emotion00, Facial00/01). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets")
	TArray<FString> MoreSetNames;

	/** The row is only on while all of these are installed (pak or mod folder names, like a pair's Requires Paks): name your swap pak. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TArray<FString> RequiresPaks;

	/** (editor 1.14) Voice: the voice bank the voice lines of the character's animations play from, in every form (a form can have its own) and in the field, e.g. /Game/Sound/Voice/{language}/Character/Player/VO_PC0010_13_YoungSephiroth (one made with Sound Banks; {language} where the voice language goes). The cues stay, the bank is this one. own or empty: the banks the animations name. Needs Create a Character System 3.9.0 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString Voice;

	/** (editor 1.14) The voice banks Voice plays in place of, e.g. /Game/Sound/Voice/{language}/Character/Player/VO_PC0010_00_Sephiroth. Empty: the character voice banks of the character's CharaSpec pack (but the ones the row and its forms switch to). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets")
	TArray<FString> VoiceReplaces;

	/** (editor 1.14) Looks From: a character blueprint, e.g. /Game/BluePrint/Character/Player/PC0000_00_Cloud_Standard (the slot's own character's), whose looks the character gets when its own blueprint has none, so the Toad status turns it into that character's frog (Sephiroth's blueprint has no frog: in Cloud's slot he kept his model and played the frog's moves). Needs Create a Character System 3.9.1 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	FString LooksFrom;

	/** (editor 1.14) AnimBlueprints From: the skeleton the AnimBlueprints of the character's slot were made for (the slot owner's, e.g. Cloud's). They run on meshes of Character Skeleton instead: for a character whose animations are all on its own skeleton, in another one's slot. Nothing else moves. Needs Character Skeleton and Create a Character System 3.8 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets")
	TSoftObjectPtr<USkeleton> AnimBlueprintsFrom;

	/** (editor 1.14) The socket of the character's mesh its weapons go to while it plays a cutscene, e.g. Attach_Weapon_Left01 (Sephiroth's cutscenes hold the Masamune in the left hand; a character on Cloud's AnimBlueprint holds it in the right). Empty: where the game puts them. Needs Create a Character System 3.6.16 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets")
	FString CutsceneWeaponSocket;

	/** (editor 1.14) The character fights as a third-person shooter (Dirge of Cerberus), as the mod's JSON has it: {"guns": [...], "camera": {...}, ...}. Empty: it does not. Needs Create a Character System 3.7 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Animation Sets", meta = (MultiLine = "true"))
	FString ShooterJson;
};

/**
 * One weapon swap: some weapons' CharaSpec packs spawn another weapon (Cloud's swords spawn Vincent's gun), so their
 * CharaSpec rows have to describe that weapon too. A row that still describes the old weapon (its model, effects and
 * sounds) next to a pack that spawns the new one keeps cutscenes with that weapon from ever starting (editor 1.6).
 */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndWeaponSwap
{
	GENERATED_BODY()

	/** Turn this swap off without deleting it. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	bool bEnabled = true;

	/** The CharaSpec rows of the weapons that are replaced, e.g. WE0000_00_Cloud_BusterSword. A name ending in * stands for every row that starts with it: WE0000_* is every one of Cloud's weapons. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TArray<FString> Weapons;

	/** The CharaSpec row of the weapon that takes their place, e.g. WE0011_00_Vincent_Quiksilver (Vincent's gun). Apply To CharaSpec makes each replaced weapon's pack in this project spawn its blueprint (Asset Class List of CharaSpec_<weapon>), then writes this weapon's model into the replaced rows, adds it to their Shared CharaSpec List, and sets their effects and sounds to what their packs load. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	FString NewWeapon;

	/** Cutscenes: Export Json adds a weapon family, the new weapon's skeleton as hub and the replaced weapons' skeleton as member, so the new weapon plays the cutscene animations made for the old one (the RebirthSkelCompat mod does this in game). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	bool bCutsceneFamily = true;

	/** The skeleton the replaced weapons' cutscene animations are made for. Empty: the first replaced weapon's own, e.g. /Game/Character/Weapon/WE0000_00_Cloud_BusterSword/Model/WE0000_00_Skeleton (Cloud's other weapons use that one too). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Weapons", meta = (EditCondition = "bCutsceneFamily"))
	TSoftObjectPtr<USkeleton> WeaponSkeleton;

	/** The new weapon's skeleton. Empty: the one in its model folder, e.g. /Game/Character/Weapon/WE0011_00_Vincent_Quiksilver/Model/WE0011_00_Skeleton. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Weapons")
	TSoftObjectPtr<USkeleton> NewWeaponSkeleton;

	/** Socket stand-ins on the new weapon, so the moves made for the old weapon still hit: each is a socket of the old weapon the moves strike with and the new weapon's socket (or bone) that takes its place, e.g. NAttack1 -> C_TrailA_a for the Buster Sword in the Masamune's place (without them the old weapon's attacks do no damage). Export Json adds them to the meshes of New Weapon Skeleton (the mod adds them while the meshes load); Validate lists the old weapon's sockets the new one lacks. Needs RebirthSkelCompat 3.2 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TArray<FEndSocketStandIn> Sockets;

	/** The weapon family and socket stand-ins are only on while all of these are installed (pak or mod folder names, like a pair's Requires Paks): name your swap pak. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TArray<FString> RequiresPaks;
};

/** Whose moves a swapped-in character plays (editor 1.7). */
UENUM(BlueprintType)
enum class EEndSwapMoveset : uint8
{
	/** The replaced character's moves: Cloud in Sephiroth's place fights and moves like Sephiroth, and Cloud's own animations fill only the names Sephiroth's lack. The rows keep their field actions (ladders, ledges). */
	Replaced UMETA(DisplayName = "Replaced character's"),
	/** The new character's own moves: Cloud fights and moves like Cloud, and the replaced character's animations fill the names Cloud's lack. Apply To CharaSpec gives the rows his field actions. */
	NewCharacter UMETA(DisplayName = "New character's own"),
};

/**
 * One character swap: another character takes the place of some CharaSpec rows (Cloud in Sephiroth's place). The rows'
 * packs (CharaSpec_<row>) spawn the new character's blueprint, and each row has to describe what its pack spawns and loads:
 * a character's blueprint on another one's model keeps the game on its loading screen (editor 1.7).
 */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndCharacterSwap
{
	GENERATED_BODY()

	/** Turn this swap off without deleting it. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characters")
	bool bEnabled = true;

	/** The CharaSpec rows of the character that is replaced, e.g. PC0010_00_Sephiroth_Standard. A name ending in * stands for every row that starts with it: PC0010_* is every one of Sephiroth's rows (wet, battle forms and VR too). Rows whose pack is not in this project and that are matched only through * are left out. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characters")
	TArray<FString> Characters;

	/** The CharaSpec row of the character that takes their place, e.g. PC0000_00_Cloud_Standard. Apply To CharaSpec makes each replaced row's pack in this project spawn his blueprint (a pack that already spawns one of his, like PC0000_22_Cloud_StandardWet for a wet row, keeps it), then makes the row describe what its pack spawns and loads: model, voice, effects, sounds and AI, with his spec in the Shared CharaSpec List. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characters")
	FString NewCharacter;

	/** Whose moves he plays in their place. Export Json makes the two skeletons a family (hub: the skeleton of the moves played) and gives the rows both characters' motion folders in this order, so the first one that has an animation name wins. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characters")
	EEndSwapMoveset Moveset = EEndSwapMoveset::Replaced;

	/** Optional: the voice he speaks with in their place, a voice bank of the game, e.g. VO_PC0000_02_Cloud_Insanity (Cloud's insanity lines) or VO_PC0000_00_Cloud. Apply To CharaSpec puts it and its lip sync (LSD_PC0000_02_Cloud_Insanity) into the packs in place of the voice they load, and into the rows. Empty: the packs keep their voice. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characters")
	FString Voice;

	/** Optional: the socket his main weapon goes to in their place, e.g. Attach_Weapon_Left01 (the left hand: Sephiroth's moves swing the sword with the left) or Attach_Weapon_Right01 (the right hand). Apply To CharaSpec writes it into the rows' Override Weapon Socket Names for weapon slot 0, the equipped weapon. Empty: the rows keep theirs. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characters")
	FString WeaponSocket;

	/** Every character keeps its own height and build: in their place he stays his own size while he plays their moves (Cloud does not grow to Sephiroth's height), and they keep theirs wherever they play his. Export Json turns "proportions" on for the swap's family, so every character of that family keeps its own bone lengths (see a pair's Keep Proportions). Needs RebirthSkelCompat 3.2 in the game (editor 1.7.1). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characters")
	bool bKeepProportions = true;

	/** The skeleton the replaced character's animations are made for. Empty: the one in the model folder of the first replaced row (the _00 one), e.g. /Game/Character/Player/PC0010_00_Sephiroth_Standard/Model/PC0010_00_Skeleton. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Characters")
	TSoftObjectPtr<USkeleton> ReplacedSkeleton;

	/** The new character's skeleton. Empty: the one in his model folder, e.g. /Game/Character/Player/PC0000_00_Cloud_Standard/Model/PC0000_00_Skeleton. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Characters")
	TSoftObjectPtr<USkeleton> NewSkeleton;

	/** The swap's family and animation set rows are only on while all of these are installed (pak or mod folder names, like a pair's Requires Paks): name your swap pak. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characters")
	TArray<FString> RequiresPaks;
};

/** One sound of a new sound bank (Sound Banks, editor 1.14): its cue and its WAV file. */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndSoundBankLine
{
	GENERATED_BODY()

	/** The sound's name in the bank: what notifies and aliases play, e.g. bt021_001_001_sep_0 (to replace a game bank's line, its cue). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks")
	FString Cue;

	/** Its WAV file (16-bit, 24-bit or float PCM, any rate, mono or stereo). Empty: <WAV Folder>/<Cue>.wav, or with Languages <WAV Folder>/<language>/<Cue>.wav. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks", meta = (FilePathFilter = "wav"))
	FFilePath Wav;

	/** How loud it plays (the game's voice lines: 0.4467, about -7 dB). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks", meta = (ClampMin = "0", ClampMax = "4"))
	float Volume = 0.4467f;

	/** Its sound category in the game's mixer (17: a voice, as the game's voice banks have it). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Sound Banks", meta = (ClampMin = "0", ClampMax = "255"))
	int32 Category = 17;

	/** Its bus in the game's mixer (19: the voice bus). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Sound Banks", meta = (ClampMin = "0", ClampMax = "255"))
	int32 Bus = 19;

	/** Its sound id in the bank (-1: the next one). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Sound Banks", meta = (ClampMin = "-1", ClampMax = "65535"))
	int32 Id = -1;

	/** The length the game takes it for (seconds; 0: the WAV's own). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Sound Banks", meta = (ClampMin = "0", ClampMax = "600"))
	float Length = 0.f;
};

/**
 * A new sound bank for the game made from WAV files (Sound Banks, editor 1.14): each line's WAV encoded as the game's
 * voice banks are (CRI HCA 2.0), in a SEAD sound bank, in a cooked SQEXSEADSound package, in a ~mods container
 * (<Container>.utoc/.ucas/.pak) the game loads as it is. A voice bank (Folder with {language}) has one package per voice
 * language: the Japanese one (the one everything names) and, with lines in several Languages, the English, French and
 * German ones. Give a character the bank with "voice" (Create a Character System 3.9.0), list it in its CharaSpec pack so
 * the game loads it, or name it in a form's sounds.
 */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndSoundBank
{
	GENERATED_BODY()

	/** Turn this bank off without deleting it. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks")
	bool bEnabled = true;

	/** The mod container's name: <Container>.utoc, .ucas and .pak (end it in _P), e.g. YoungSephirothVoice_P. Put the three files in ~mods. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks")
	FString Container = TEXT("MyVoice_P");

	/** The bank's name (and its asset's): 1-31 letters, digits, _ or -, e.g. VO_PC0010_13_YoungSephiroth. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks")
	FString Bank;

	/** Its bank id in the game's sound engine (0: made from the name). Two banks loaded at once need different ids. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Sound Banks", meta = (ClampMin = "0", ClampMax = "65535"))
	int32 BankId = 0;

	/** Where it goes in the game: /Game/Sound/Voice/{language}/Character/Player for a character's voice bank ({language} where the voice language goes), or any /Game/... folder for one bank (sound effects). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks")
	FString Folder = TEXT("/Game/Sound/Voice/{language}/Character/Player");

	/** The alias setting its cues go through (the game's battle voice picks lines by alias), e.g. /Game/Sound/Config/AliasSetting/VO_PC0010_00_Sephiroth: a bank made to stand in for a game bank takes that bank's. Empty: none. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks")
	FString AliasSetting;

	/** How it fades with distance: a Sound Attenuation of the game's, e.g. /Game/Sound/Config/Attenuation/player. Empty: none. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks")
	FString Attenuation = TEXT("/Game/Sound/Config/Attenuation/player");

	/** The encoding's bit rate per channel (kbps; the game's voice banks: 85.25). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Sound Banks", meta = (ClampMin = "16", ClampMax = "512"))
	float Kbps = 85.25f;

	/** The WAVs resampled to this rate first (the game's voice lines: 32000). 0: each WAV's own. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Sound Banks", meta = (ClampMin = "0", ClampMax = "96000"))
	int32 SampleRate = 32000;

	/** The WAVs mixed down to this many channels first (the game's voice lines: 1). 0: each WAV's own. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Sound Banks", meta = (ClampMin = "0", ClampMax = "8"))
	int32 Channels = 1;

	/** The folder of the WAVs: <Cue>.wav each, or with Languages a folder per language (US, JP, FR, DE) of them. Read Sound Bank WAVs fills the lines from it. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks")
	FDirectoryPath WavFolder;

	/** The voice languages the lines have (each a folder of WAV Folder), e.g. US and JP. Empty: one set of lines, which every voice language plays. Only for a voice bank (Folder with {language}). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks")
	TArray<FString> Languages;

	/** The bank's sounds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks")
	TArray<FEndSoundBankLine> Lines;

	/** Where Build Sound Banks writes the container. Empty: <Project>/Saved/RebirthSkelCompat/SoundBanks/<Container>. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks")
	FDirectoryPath OutputFolder;
};

/**
 * (editor 1.15) A skin: another model a character wears in game, kept as a folder of the game's own packages and a
 * skin.json (skins\<Folder> in the game's Create a Character System folder) in place of a pak, so any number of skins
 * can be installed at once. Build Skins cooks its model (with the model's skeleton and physics asset, and its Extra
 * Assets) into the game's package format, writes the folder, installs it and puts every installed skin into one ~mods
 * container (CreateACharacterSkins_P) the game mounts. The model's skeleton joins Family, so the skin plays every
 * animation of the character's family. Needs Create a Character System 3.10 in the game.
 */
USTRUCT(BlueprintType)
struct REBIRTHSKELCOMPATEDITOR_API FEndCharacterSkin
{
	GENERATED_BODY()

	/** Turn this skin off without deleting it: Build Skins skips it (a copy installed before stays as it is). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	bool bEnabled = true;

	/** The skin's name on the skins menu, e.g. Remake Sephiroth. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	FString Name;

	/** Its folder's name (skins\<Folder>): letters, digits, _ and -. Empty: the Name's letters and digits (Remake Sephiroth: RemakeSephiroth). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	FString Folder;

	/** The model: a Skeletal Mesh of this project, e.g. /Game/GameContents/Character/Enemy/EB0021_00_Sephiroth_Standard/Model/EB0021_00. Its skeleton and physics asset go into the skin with it (one the game has stays the game's). Its materials have to be in the game, in Extra Assets or in a mod (your game materials mod): Build Skins lists the ones that are not in the game or the skin. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	TSoftObjectPtr<USkeletalMesh> Model;

	/** The CharaSpec rows whose character wears it, e.g. PC0000_00_Cloud_Standard (every row of the character's slot: Cloud's rows for the Fully Playable Sephiroth and Young Sephiroth). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	TArray<FString> Characters;

	/** The skeleton family the model's skeleton joins: its hub, the character's skeleton, e.g. PC0010_00_Skeleton (Sephiroth's). Then the model plays every animation made for the family. Empty: the model is on the character's own skeleton. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	TSoftObjectPtr<USkeleton> Family;

	/** The model keeps its own proportions while it plays the family's animations (a pair's Keep Proportions). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	bool bKeepProportions = false;

	/** More bones that keep the model's own length with Keep Proportions, as patterns: R_Feather* is every bone starting with R_Feather. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Skins", meta = (EditCondition = "bKeepProportions"))
	TArray<FString> ProportionBones;

	/** The voice while it is worn: own (the banks its animations name: the original voice, e.g. adult Sephiroth's in place of the young voice a row gives him), a voice bank such as /Game/Sound/Voice/{language}/Character/Player/VO_PC0010_00_Sephiroth, or empty (the row's Voice). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	FString Voice;

	/** The weapon it fights with while it is worn: a weapon blueprint class, e.g. /Game/BluePrint/Character/Weapon/WE1021_10_SephirothIllusion_MasamuneCutScale.WE1021_10_SephirothIllusion_MasamuneCutScale_C. Empty: the character's own. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	FString Weapon;

	/** The AnimBlueprint the model runs (an AnimBlueprint asset or its _C class). Empty: the character's own (a model of the same body). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Skins")
	FString AnimBlueprint;

	/** More assets of this project cooked into the skin: materials and textures the game and your mods do not have. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	TArray<FSoftObjectPath> ExtraAssets;

	/** Who made it (the skins menu shows it). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	FString Author;

	/** A line or two about it (the skins menu shows it). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins", meta = (MultiLine = "true"))
	FString Description;

	/** A picture of it for the skins menu (.png), copied into its folder as preview.png. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins", meta = (FilePathFilter = "png"))
	FFilePath Preview;
};

/**
 * Skeleton compatibility data object: the KH3 "compatible skeletons" list for Rebirth.
 *
 * Editor only (never cooked). The list reaches the game through the RebirthSkelCompat UE4SS mod as JSON
 * (Export Json; no cook needed). Mesh rebind pairs can instead be stamped into the receiving skeleton's
 * Asset User Data (Apply To Skeletons; it cooks with your pak).
 */
UCLASS(BlueprintType, meta = (DisplayName = "Skeleton Compatibility Data Object"))
class REBIRTHSKELCOMPATEDITOR_API UEndSkeletonCompatDataObject : public UDataAsset
{
	GENERATED_BODY()

public:
	UEndSkeletonCompatDataObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeleton Compatibility")
	TArray<FEndSkeletonCompatPair> Pairs;

	/** Which animations characters play: battle and field sets built from other characters' sets (Auto Match, 3.2), moves, limit breaks, socket stand-ins, proportions, field actions and cutscenes. Pairs or families still decide which skeleton can play which animations. Needs RebirthSkelCompat 3.1 in the game (3.2 for the options marked so). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sets")
	TArray<FEndAnimSetRow> AnimationSets;

	/** Characters that another character takes the place of (Cloud in Sephiroth's place): Apply To CharaSpec makes their packs spawn him (with the Voice you choose) and their rows describe him (model, voice, effects, sounds, AI, his spec shared, the Weapon Socket), and Export Json makes the two skeletons a family and gives the rows the moves chosen (Moveset). Put his weapon in their hands with a weapon swap. Needs RebirthSkelCompat 3.1 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characters")
	TArray<FEndCharacterSwap> CharacterSwaps;

	/** Weapons that another weapon takes the place of (Cloud's swords -> Vincent's gun): Apply To CharaSpec makes their packs spawn the new weapon and their CharaSpec rows describe it, so cutscenes with them start, Export Json adds a weapon family so the new weapon plays their cutscene animations, and the swap's Sockets let the old weapon's moves hit with the new one. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TArray<FEndWeaponSwap> WeaponSwaps;

	/** (editor 1.14) New sound banks made from WAV files: a character's own voice (Voice on its row or forms), new sound effects. Read Sound Bank WAVs fills each bank's lines from its WAV Folder; Build Sound Banks writes each as a ~mods container the game loads as it is. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Banks")
	TArray<FEndSoundBank> SoundBanks;

	/** (editor 1.15) Skins: other models characters wear in game, each a folder of the game's own packages and a skin.json in place of a pak, any number installed at once. Build Skins builds them into Skins Output Folder, installs them into Game Directory's Create a Character System folder (skins) and puts every installed skin into one ~mods container (CreateACharacterSkins_P). Needs Create a Character System 3.10 in the game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	TArray<FEndCharacterSkin> Skins;

	/** Where Build Skins writes the skin folders (and its work files, in _work). Empty: <Project>/Saved/RebirthSkelCompat/Skins. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	FDirectoryPath SkinsOutputFolder;

	/** Build Skins also copies each skin into Game Directory's Create a Character System folder (ue4ss\Mods\RebirthSkelCompat\skins\<Folder>) and makes the skins container (~mods\CreateACharacterSkins_P) anew from every installed skin. Close the game first: it keeps the container open. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skins")
	bool bInstallSkins = true;

	/** The project's CharaSpec table (made editable), which Validate reads and Apply To CharaSpec edits. */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Animation Sets")
	FString CharaSpecTable = TEXT("/Game/DataObject/Resident/CharaSpec");

	/** Apply To CharaSpec also points NoBattleCharaSpec / ReserveCharaSpec of the rows' characters at the row itself when they name a row that is not in the table (the way swap mods do it; a missing row keeps the game on its loading screen). */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Animation Sets")
	bool bFixMissingRowReferences = true;

	/** Apply To CharaSpec also checks every CharaSpec pack of this project against its row, and gives a row whose model is not the blueprint its pack spawns that blueprint's model (one character's or weapon's blueprint on another one's model keeps the game on its loading screen, or keeps cutscenes with that weapon from starting). Validate lists every pack that disagrees with its row either way. */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Characters")
	bool bFixPackModels = true;

	/** Apply To CharaSpec also edits the swaps' packs in this project (CharaSpec_<row>): the blueprint they spawn, a character swap's Voice and lip sync, a weapon swap's effect pack. Game assets this project does not have are kept as references to the game's own (Rebirth Cooked Asset Preview plugin). Off: only the CharaSpec rows change, and a pack that does not spawn the new character or weapon yet is reported. */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Characters")
	bool bApplyToPacks = true;

	/** Apply To Skeletons also registers each pair with this editor's skeleton compatibility (RebirthMaterialPreview), for Persona previews. Family pairs are registered both ways. */
	UPROPERTY(EditAnywhere, Category = "Skeleton Compatibility", AdvancedDisplay)
	bool bRegisterForEditorPreview = true;

	/** Export Json writes <AssetName>.skelcompat.json here. Empty = <Project>/Saved/RebirthSkelCompat. Ship it next to your pak in ~mods. */
	UPROPERTY(EditAnywhere, Category = "Export")
	FDirectoryPath ExportDirectory;

	/** Import From Game Json reads this file when set (any compat JSON, e.g. one you were given), instead of this data object's own compat\<AssetName>.json. */
	UPROPERTY(EditAnywhere, Category = "Export", meta = (FilePathFilter = "json"))
	FFilePath ImportFile;

	/** FINAL FANTASY VII REBIRTH install folder. If RebirthSkelCompat is installed there, Export Json also writes its compat\<AssetName>.json, and Validate shows how the game combines this data object with the other compat files and the installed paks. */
	UPROPERTY(EditAnywhere, Category = "Export")
	FDirectoryPath GameDirectory;

	/** Result of the last button press. */
	UPROPERTY(VisibleAnywhere, Transient, Category = "Skeleton Compatibility", meta = (MultiLine = "true"))
	FString LastResult;

	/** Check every pair: the assets load, how many bones and curves carry over, each mesh against the game's bone-hierarchy test, and how the game combines these pairs with the other compat files (families, outfits that follow animations, pairs that switch off). Animation set rows, character swaps and weapon swaps are checked against the CharaSpec table and the packs in this project (what Apply To CharaSpec would change, shared specs that would load each other in a loop, packs that disagree with their rows). */
	UFUNCTION(CallInEditor, Category = "Skeleton Compatibility")
	void Validate();

	/** Mesh rebind pairs: put the list on each receiving skeleton's Asset User Data (BP_SkelCompatUserData), then save. With animation set rows or weapon swaps it also does Apply To CharaSpec (field actions, weapon rows) and saves the CharaSpec table. Cook and pak as usual; families and the rest reach the game through Export Json. */
	UFUNCTION(CallInEditor, Category = "Skeleton Compatibility")
	void ApplyToSkeletons();

	/** Remove BP_SkelCompatUserData from each receiving skeleton, then save. */
	UFUNCTION(CallInEditor, Category = "Skeleton Compatibility")
	void RemoveFromSkeletons();

	/** Write the runtime JSON the RebirthSkelCompat mod reads: pairs, families, animation set rows, the character swaps' families and moves, and the weapon swaps' families and socket stand-ins (no cook needed). */
	UFUNCTION(CallInEditor, Category = "Skeleton Compatibility")
	void ExportJson();

	/** Take Method, Requires Paks, Adopt Paths and the mesh options over from this data object's JSON in the game's compat folder (or Import File), matched by receiving skeleton; pairs and families this data object does not have are added. Animation set rows are matched by character, weapon swaps by new weapon, character swaps by new character and replaced rows. */
	UFUNCTION(CallInEditor, Category = "Skeleton Compatibility")
	void ImportFromGameJson();

	/** Animation set rows: write each row's Field Actions folder into its characters' CharaSpec rows (AnimationSetParentFolder) and fix references to rows that are not in the table (if Fix Missing Row References is on). Character swaps: make each replaced row's pack in this project spawn the new character (and speak with the swap's Voice), then the row describe what its pack spawns and loads (model, voice, effects, sounds, AI, his spec shared, Weapon Socket, his field actions for his own moveset). Weapon swaps: make each replaced weapon's pack spawn the new weapon, then its row describe it (model, Shared CharaSpec List, the effects and sounds its pack loads). Fix Pack Models: every other pack's row gets the model of the blueprint its pack spawns. Then save the packs and the CharaSpec table. Cook them with your mod. */
	UFUNCTION(CallInEditor, Category = "Animation Sets")
	void ApplyToCharaSpec();

	/** (editor 1.14) Every sound bank's lines from its WAV Folder: a line for each WAV (its name the cue; with Languages, the WAVs of the first language's folder), the lines it has keeping their settings. */
	UFUNCTION(CallInEditor, Category = "Sound Banks")
	void ReadSoundBankWavs();

	/** (editor 1.14) Encode every sound bank's WAVs and write it as a ~mods container (<Container>.utoc, .ucas, .pak in its Output Folder) the game loads as it is. */
	UFUNCTION(CallInEditor, Category = "Sound Banks")
	void BuildSoundBanks();

	/** (editor 1.14) Read Sound Bank WAVs without a dialog. Returns a report. */
	UFUNCTION(BlueprintCallable, Category = "Sound Banks")
	bool ReadSoundBankWavsTo(FString& OutReport);

	/** (editor 1.14) Build Sound Banks without a dialog (for scripts). Returns a report. */
	UFUNCTION(BlueprintCallable, Category = "Sound Banks")
	bool BuildSoundBanksTo(FString& OutReport);

	/** (editor 1.15) Build every skin that is on: its packages cooked here for the game (WindowsNoEditor, as the cooker saves them), turned into the game's own package format by the engine's IoStore commandlet (about 20 s), written with its skin.json into Skins Output Folder/<Folder>; with Install Skins on, copied into the game and every installed skin put into the skins container (~mods\CreateACharacterSkins_P). Lists the material slots whose materials have to come from a mod and the model's bones its Family lacks. */
	UFUNCTION(CallInEditor, Category = "Skins")
	void BuildSkins();

	/** (editor 1.15) Build Skins without a dialog (for scripts). Returns a report. */
	UFUNCTION(BlueprintCallable, Category = "Skins")
	bool BuildSkinsTo(FString& OutReport);

	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	bool ApplyRowsToCharaSpec(FString& OutReport);

	/** Animation set rows: put each row's socket stand-ins on the meshes of its Character Skeleton in this project (a copy of the Use socket, or a socket on the Use bone, under the game's socket name), so the weapon shows in Persona and the sockets cook with your pak. Cooked game meshes cannot be saved: the game mod adds the stand-ins to those while they load. */
	UFUNCTION(CallInEditor, Category = "Animation Sets")
	void ApplySocketStandIns();

	/** Remove the socket stand-ins that Apply Socket Stand-ins put on the meshes of each row's Character Skeleton. */
	UFUNCTION(CallInEditor, Category = "Animation Sets")
	void RemoveSocketStandIns();

	/** Animation set rows: make an AnimComposite asset of every chained move and limit break (Then Play) in Chain Folder, to preview and edit it in Persona. In game the mod builds the same chain by itself; to play your edited asset instead, set the move's Animation to it, clear Then Play, and cook the asset with your mod. The animations have to be in this project. */
	UFUNCTION(CallInEditor, Category = "Animation Sets")
	void MakeChainAssets();

	/** Animation set rows: build every move with Build on (see Build on a move), then save. Press it again after changing a move: the built animations are made anew. */
	UFUNCTION(CallInEditor, Category = "Animation Sets")
	void BuildMoves();

	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	bool BuildMoveAnimations(FString& OutReport);

	/** Open the Move Maker on this data object: pick a character (an animation set row), the attack, ability or limit break to make, and any animation to make it from (another character's, the game's, or an imported one); scrub it in the animation editor to set its hits, add effects and sounds, then Build. Also in Window > Rebirth Move Maker. */
	UFUNCTION(CallInEditor, Category = "Animation Sets")
	void OpenMoveMaker();

	/** Build one move of one animation set row (Name and Set as the move has them), then save it. */
	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	bool BuildOneMove(int32 RowIndex, const FString& Name, const FString& Set, FString& OutReport);

	/** Key animations (editor 1.10): make an Anim Sequence on Skeleton from every key animation file in Folder (.cacanim:
	 * each bone's local translation, rotation and scale per frame, in Unreal's axes and on the skeleton's bone names, as the
	 * Create a Character System tools write them for animations from other games), each into Destination/<file name>, e.g.
	 * /Game/RebirthSkelCompat/Imported/KH2Sephiroth. An earlier import of the same name is made anew. They get the game's
	 * ACL compression settings, so Build Moves can make moves from them. */
	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	static bool ImportKeyAnimations(const FString& Folder, const FString& SkeletonPath, const FString& Destination, FString& OutReport);

	/** For planning moves (editor 1.10.2): each animation's (or animation pack's) length, frames, root motion settings and
	 * notifies (time, duration, track, class, whether Build Moves counts it as a hit or as the motion's own sound or effect,
	 * and its settings that differ from the class default), or a pack's animations, as JSON. */
	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	static FString DescribeAnimations(const TArray<FString>& AnimationPaths);

	/** Notifies as they are (editor 1.13): every notify of each animation in From Paths (gameplay notifies, the motion's sounds
	 * and effects, cloth settings) copied onto the animation at the same place in To Paths with every setting the original has
	 * (links to sound banks and effects that are not in this project, and values the editor's own types have no name for,
	 * too), at the same times (scaled when the lengths differ) and on the same tracks, with its sync markers and curves. For
	 * animations made frame for frame from another character's, e.g. retargeted key animations. Replace: the To animation's
	 * notifies, sync markers and curves are taken out first. Saves the To animations and returns a report. */
	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	static FString CopyNotifiesOnto(const TArray<FString>& FromPaths, const TArray<FString>& ToPaths, bool bReplace);

	/** Flatten Root (editor 1.13.1): the skeleton's root bone made to rest with no rotation and a scale of 1, the way the
	 * game's own skeletons rest (Cloud's Trans), for a model whose export left a turn on its root bone (a Blender armature's
	 * rotation, or another game's axes). The game stands, steers and turns a character by its root at rest, so a turned
	 * root makes it face one way and move another. Every other bone keeps its place: the root's children take the root's
	 * old turn into their own rest, on the skeleton, on every mesh of it and in every animation of it (their keys under the
	 * root), so every pose stays the same in game. Bone Renames renames bones on the skeleton, its meshes, their sockets
	 * and the animations' tracks (e.g. trans = Transform). Run it once with bAnimations off (the skeleton and its meshes,
	 * saved), then with bAnimations on for Count animations at a time from First (the skeleton's animations sorted by path,
	 * additive ones last) until the report says none are left; an animation already done is skipped. Returns a report. A
	 * mesh reimported from the same file later comes back turned: run it again. */
	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	static FString FlattenSkeletonRoot(const FString& SkeletonPath, const TMap<FString, FString>& BoneRenames, bool bAnimations, int32 First, int32 Count);

	/** Cook For Game (editor 1.13.1): each package saved the way the cooker saves it for the game (WindowsNoEditor), into
	 * OutContentDir/<its path under /Game>.uasset, like Rebirth's Cook Asset To File; an Anim Sequence is first compressed
	 * anew with the game's ACL settings (safety fallback off) and its compressed bytes made ready for the save, so an
	 * animation compressed again in this session (edited, flattened, opened in Persona) does not stop the editor while it
	 * cooks. Returns a report: one line per package that failed and a summary. */
	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	static FString CookPackagesForGame(const TArray<FString>& PackageNames, const FString& OutContentDir);

	// The Move Maker's view of this data object (editor 1.8).
	TArray<FString> MoveMakerRowLabels() const;
	/** The animation names the row's character has of that kind (from its battle sets in this project), with their lengths: "B_NAttack01_0 (1.27 s)". */
	TArray<FString> MoveMakerSlots(int32 RowIndex, EEndMoveSlotKind Kind) const;
	int32 FindMove(int32 RowIndex, const FString& Name, const FString& Set) const;
	const FEndAnimSetMove* GetMove(int32 RowIndex, int32 MoveIndex) const;
	/** Adds the move to the row, or replaces the row's move of the same name and set. */
	void SetMove(int32 RowIndex, const FEndAnimSetMove& Move);
	FString BuiltMoveObjectPath(int32 RowIndex, const FEndAnimSetMove& Move) const;
	/** The animation a build of Move copies its gameplay notifies from (empty: none found), and where it was looked for. */
	FString MoveNotifySourcePath(int32 RowIndex, const FEndAnimSetMove& Move, FString& OutLookedFor) const;
	/** The row's Character Skeleton, loaded (null when not set). */
	USkeleton* CharacterSkeletonOf(int32 RowIndex) const;

	/** The chunk Build Moves labels the built animations for (a Primary Asset Label in each Build Folder, Label Assets In My Directory on), so Package Project puts them in pakchunk<N>. 0 or less: no label. */
	UPROPERTY(EditAnywhere, Category = "Animation Sets")
	int32 BuildChunk = 46;

	/** Where Make Chain Assets puts the AnimComposites. */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Animation Sets")
	FString ChainFolder = TEXT("/Game/RebirthSkelCompat/Chains");

	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	bool ApplySocketStandInsToMeshes(bool bRemove, FString& OutReport);

	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	bool MakeChainAnimComposites(FString& OutReport);

	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	bool ValidatePairs(FString& OutReport) const;

	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	FString ToRuntimeJson() const;

	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	bool WriteRuntimeJson(FString& OutReport) const;

	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	bool ApplyPairsToSkeletons(bool bRemove, FString& OutReport);

	UFUNCTION(BlueprintCallable, Category = "Skeleton Compatibility")
	bool ImportRuntimeJson(FString& OutReport);

	virtual bool IsEditorOnly() const override { return true; }

private:
	void ShowResult(const FString& Title, const FString& Report, bool bOk);
	FString GameCompatFile() const;
	/** Builds the moves with Build on that Pick accepts (row index, move), then saves them. */
	bool BuildMovesWhere(TFunctionRef<bool(int32, const FEndAnimSetMove&)> Pick, FString& OutReport);
};
