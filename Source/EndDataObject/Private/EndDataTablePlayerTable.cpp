#include "EndDataTablePlayerTable.h"

FEndDataTablePlayerTable::FEndDataTablePlayerTable() {
    this->PlayerType = 0;
    this->FavPointPriority = 0;
    this->ExcludeMateriaListFlag = 0;
    this->ExcludeEquipmentListFlag = 0;
    this->IgnoreBattleReward = 0;
    this->NotifyLevelUpMessage = 0;
    this->NotifySPUpMessage = 0;
}



FArchive& operator<<(FArchive& Ar, FEndDataTablePlayerTable& Table)
{
    // Now serialize each field in FEndDataTablePlayerTable
    Ar << Table.PlayerType;
    Ar << Table.TextId;
    Ar << Table.ActorName;
    Ar << Table.LastBattleInfoResidentParameterID;
    Ar << Table.FavPointPriority;
    Ar << Table.SwitchFavPointResidentWorkStoryFlagID;
    Ar << Table.SwitchFavPointResidentWorkID;
    Ar << Table.PlayerParameterStringFormat;
    Ar << Table.WeaponUpgradeTreeLevelFormat;
    Ar << Table.PCReinforcedFormat;
    Ar << Table.PlayerFavRankFormat;
    Ar << Table.FavMapIconID;
    Ar << Table.ConfigFavPointStoryFlag;
    Ar << Table.ConfigFavPointStoryFlagChapter12;
    Ar << Table.RegularMemberJoinFlag;
    Ar << Table.EquipListAddFlag;
    Ar << Table.EquipmentOpenMenuFlag;
    Ar << Table.MateriaOpenMenuFlag;
    Ar << Table.ExcludeMateriaListFlag;
    Ar << Table.ExcludeEquipmentListFlag;
    Ar << Table.IgnoreBattleReward;
    Ar << Table.TargetSuppLocID;
    Ar << Table.CautionAttackResponseArea;
    Ar << Table.EventStoryFlag_Array;
    Ar << Table.EventCharaSpec_Array;
    Ar << Table.SeeChangeCloth_Array;
    Ar << Table.PlayerCharaSpec_Array;
    Ar << Table.ChangeWeaponStoryFlag_Array;
    Ar << Table.ChangeWeaponCharaSpec_Array;
    Ar << Table.NotifyLevelUpMessage;
    Ar << Table.NotifySPUpMessage;

    // Return the FArchive& for chaining
    return Ar;
}