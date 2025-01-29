#include "EndMainPlaylogList.h"

UEndMainPlaylogList::UEndMainPlaylogList() {
    this->StoneBox = NULL;
    this->Txt_Category = NULL;
    this->Billboard_CharaImg = NULL;
    this->Icon_Clear = NULL;
    this->CharaList_1 = NULL;
    this->CharaList_2 = NULL;
    this->Total_Gauge = NULL;
    this->Txt_Total = NULL;
    this->Icon_Favor = NULL;
}

void UEndMainPlaylogList::OnLogListSetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}

void UEndMainPlaylogList::OnCharaList2SetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}

void UEndMainPlaylogList::OnCharaList1SetupItem(UWidget* ItemWidget, int32 ItemIndex) {
}


