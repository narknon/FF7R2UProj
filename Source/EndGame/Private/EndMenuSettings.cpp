#include "EndMenuSettings.h"

UEndMenuSettings::UEndMenuSettings() {
    this->ColorMappings.AddDefaulted(14);
    this->ButtonMappings.AddDefaulted(358);
    this->FieldMemoMappings.AddDefaulted(1);
    this->GoldSaucerShopMappings.AddDefaulted(7);
    this->MenuBattleAngleY = 20.00f;
    this->SubtitleWaitTime = 0.10f;
    this->PlayTimeSleepTime = 180.00f;
    this->MaxCompassIconDistance = 20000.00f;
    this->MaxCompassIconDistanceInsideLocation = 6000.00f;
    this->CompassNormalIconScale = 0.00f;
    this->MaxFieldQuestIconDistance = 4000.00f;
    this->MaxFieldQuestIconDistanceInsideLocation = 2000.00f;
    this->ChangeMapStickHoldTime = 0.40f;
    this->CloudFirstNameId = TEXT("$menu_partyname_0000_0002");
    this->BarretFirstNameId = TEXT("$menu_partyname_0001_0002");
    this->TifaFirstNameId = TEXT("$menu_partyname_0002_0002");
    this->AerithFirstNameId = TEXT("$menu_partyname_0003_0002");
    this->RedxiiiFirstNameId = TEXT("$menu_partyname_0004_0002");
    this->YuffieFirstNameId = TEXT("$menu_partyname_0005_0002");
    this->CaitSithFirstNameId = TEXT("$menu_partyname_0006_0002");
    this->ZackFirstNameId = TEXT("$menu_partyname_0007_0002");
    this->SephirothFirstNameId = TEXT("$menu_partyname_0008_0002");
    this->CloudLastNameId = TEXT("$menu_partyname_0000_0003");
    this->BarretLastNameId = TEXT("$menu_partyname_0001_0003");
    this->TifaLastNameId = TEXT("$menu_partyname_0002_0003");
    this->AerithLastNameId = TEXT("$menu_partyname_0003_0003");
    this->YuffieLastNameId = TEXT("$menu_partyname_0005_0003");
    this->ZackLastNameId = TEXT("$menu_partyname_0007_0003");
    this->CloudReleaseId = TEXT("stfComn_Release_Equipment_Cloud");
    this->BarretReleaseId = TEXT("stfComn_Release_Equipment_Barret");
    this->TifaReleaseId = TEXT("stfComn_Release_Equipment_Tifa");
    this->AerithReleaseId = TEXT("stfComn_Release_Equipment_Aerith");
    this->RedxiiiReleaseId = TEXT("stfComn_Release_Equipment_RedXIII");
    this->YuffieReleaseId = TEXT("stfComn_Release_Equipment_Yuffie");
    this->CaitSithReleaseId = TEXT("stfComn_Release_Equipment_Caitsith");
}


